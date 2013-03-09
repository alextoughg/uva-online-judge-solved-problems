#include <iostream>
#include <string.h>
#include <queue>
#define MAX 200
using namespace std;


bool M[MAX][MAX];
int color[MAX];
bool seen[MAX];

// Whether a bicoloring is possible on a graph with n nodes.
bool bicoloring(int n){
    queue<int> q; // The BFS queue to represent the visited set.
    int s = 0; // The source vertex.

    for(int v=0;v<n;v++) {
        color[v] = -1; // each vertex is initially uncolored.
        seen[v] = false; // we haven't visited any nodes yet.
    }
    color[s] = 0; // color source red.
    seen[s] = true;
    q.push(s); // put source vertex into queue.

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v=0;v<n;v++){ 
            if(M[u][v] && !seen[v] && (color[v] == -1)){
                color[v] = (color[u] + 1) % 2;
                seen[v] = true;
                q.push(v);
            }
            // Successor has same color as predecessor, bicoloring is not possible!
            if(M[u][v] && (color[u] == color[v])) return false;
        }
    }
    return true;
}

int main(){
    int n;
    while(cin >> n){
        memset(M, false, sizeof(M));
        if(!n) break;
        int elle;
        cin >> elle;
        int b,e;
        for(int i=0;i<elle;i++) {
            cin >> b >> e;
            M[b][e] = true;
        }
        bool p = bicoloring(n);
        if(p) cout << "BICOLORABLE." << endl;
        else cout << "NOT BICOLORABLE." << endl;
    }
    return 0;
}
