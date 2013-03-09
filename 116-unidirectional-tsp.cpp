#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#define MIN(a,b) (a<b ? a : b)
#define A(i,m) (i == -1 ? m-1 : (i == m ? 0 : i))
#define INF 0x3f3f3f3f
using namespace std;

// State: coordinates of where you begin (i,j).
// Recurrence relation: min_cost(i,j) = (M[i,j],i)  if j == n-1, 
//                                      (min(min_cost(i-1,j+1).cost, (diagonal up)
//                                          min_cost(i,j+1).cost,   (to the right)
//                                          min_cost(i+1,j+1).cost)        (diagonal down),
//                                      i ++ min(min_cost(i-1,j+1).path, (diagonal up)
//                                          min_cost(i,j+1).path,   (to the right)
//                                          min_cost(i+1,j+1).path)  
// If i=-1, then i=m-1. If i=m, then i=0. (in my little magical world)
// All the hard work has been done!


int m,n; // number of rows,columns

class cont_t{
    public:
        int cost;
        string path; //since rows are between 1 and 10 (0 and 9).
        cont_t() : cost(INF), path("") {}
};

bool operator<(const cont_t &x, const cont_t &y)
{
    if(x.cost != y.cost) return x.cost < y.cost;
    else  return x.path.compare(y.path) < 0;
}

cont_t memo[10][100];
int M[10][100]; // initialized to 0


cont_t min_cost(int i, int j)
{
    cont_t r;
    // Base cases of recurrence
    if(j == (n-1)) {
        r.cost = M[i][j];
        stringstream ss;
        ss << i+1;
        ss >> r.path;
        return r;
    }
    if(memo[i][j].cost != INF) return memo[i][j];


    cont_t a = min_cost(A(i-1,m),j+1);
    cont_t b = min_cost(A(i,m),j+1);
    cont_t c = min_cost(A(i+1,m),j+1);
    cont_t mm = MIN(a,MIN(b,c)); 

    
    r.cost = M[i][j] + mm.cost;

    stringstream ss;
    string k;
    ss << i+1;
    ss >> k;
    r.path = k + " " + mm.path;

    return memo[i][j] = r;

}

int main()
{
    while (cin >> m >> n){
        for(int i=0;i<10;i++)
            for(int j=0;j<100;j++)
                memo[i][j] = cont_t();
        memset(M, 0, sizeof(M));
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                cin >> M[i][j];
        cont_t h;
        for(int i=0;i<m;i++)
            h = MIN(h, min_cost(i,0));
        cout << h.path << endl;
        cout << h.cost << endl;
    }
    return 0;
}
