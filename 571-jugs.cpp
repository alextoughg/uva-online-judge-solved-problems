#include <iostream>
#include <queue>
#include <string.h>

using namespace std;

struct state_t {
  state_t(int A_, int B_, int cost_)
      : A(A_), B(B_), cost(cost_) {}
  bool operator< (const state_t& s) const {
    return s.cost < cost;
  }
  int A;
  int B;
  int cost;
};

struct node_t {
  node_t()
      : i(-1), j(-1), action(-1) {}
  node_t(int i_, int j_, int action_)
      : i(i_), j(j_), action(action_) {} 
  int i;
  int j;
  int action; 
};

const int INFINITE = 0x3f3f3f3f; // Good value for memset()
int minCost[1001][1001];         // Indexed by [state_t::A][state_t::B]
node_t actions[1001][1001];      // Indexed by [state_t::A][state_t::B]

void AddToFringe(priority_queue<state_t>& fringe, int A, int B, int cost, int i, int j, int action) {
    if(cost < minCost[A][B]){
        minCost[A][B] = cost;
        actions[A][B] = node_t(i, j, action);
        fringe.push(state_t(A, B, cost));
    }
}

int Dijkstra(int Ca, int Cb, int N){
    const int CapA = Ca, CapB = Cb, Goal = N;
    memset(minCost, INFINITE, sizeof(minCost));
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 100; j++)
            actions[i][j] = node_t();
    priority_queue<state_t> fringe;
    for(AddToFringe(fringe, 0, 0, 0, -1, -1, 0); !fringe.empty();){
        
        // Take next state, check if a better one was already 
        // processed or it is a final state.
        const state_t s = fringe.top(); fringe.pop();
        if(s.cost > minCost[s.A][s.B]) continue;
        if(s.B == Goal){
            
            // Simple backtracking algorithm using actions 2-d array.
            int path[s.cost];
            int k = s.cost-1;
            int a = s.A, b = s.B;
            // Lesson: always copy entries in an array into a variable.
            // Saves you a headache and is very efficient.
            node_t n = actions[a][b];
            while(n.action != 0){
                path[k] = n.action;
                a = n.i;
                b = n.j;
                n = actions[a][b];
                k--;
            }
            for(int c = 0; c < s.cost; c++){
                switch(path[c]){
                    case 1: cout << "fill A" << endl; break;
                    case 2: cout << "fill B" << endl; break;
                    case 3: cout << "empty A" << endl; break;
                    case 4: cout << "empty B" << endl; break;
                    case 5: cout << "pour A B" << endl; break;
                    case 6: cout << "pour B A" << endl; break;
                    default: break;
                }
            }
            cout << "success" << endl;
            return 1;
        }
        
        // The following transitions are possible from the current state:
        // 1. If s.A < CapA, fill A.
        // 2. If s.B < CapB, fill B.
        // 3. If s.A > 0, empty A.
        // 4. If s.B > 0, empty B.
        // 5. If s.B != CapB and s.A > 0, then pour from A to B. Two cases:
        //      (a) CapB - s.B >= s.A, then B is NOT going to fill up. A will empty.
        //      (b) CapB - s.B < s.A, then B is going to fill up. A will not be empty.
        // 6. If s.A != CapA and s.B > 0, then pour from B to A. Two cases:
        //      (a) CapA - s.A >= s.B, then A is NOT going to fill up. B will empty.
        //      (b) CapA - s.A < s.B, then A is going to fill up. B will not be empty.

        if(s.A < CapA) 
            AddToFringe(fringe, CapA, s.B, s.cost + 1, s.A, s.B, 1);
        if(s.B < CapB)
            AddToFringe(fringe, s.A, CapB, s.cost + 1, s.A, s.B, 2);
        if(s.A > 0)
            AddToFringe(fringe, 0, s.B, s.cost + 1, s.A, s.B, 3);
        if(s.B > 0)
            AddToFringe(fringe, s.A, 0, s.cost + 1, s.A, s.B, 4);
        if(s.B != CapB && s.A > 0){
            if(CapB - s.B >= s.A)
                AddToFringe(fringe, 0, s.B + s.A , s.cost + 1, s.A, s.B, 5);
            else
                AddToFringe(fringe, s.A - (CapB - s.B), CapB, s.cost + 1, s.A, s.B, 5);
        }
        if(s.A != CapA && s.B > 0){
            if(CapA - s.A >= s.B)
                AddToFringe(fringe, s.B + s.A , 0, s.cost + 1, s.A, s.B, 6);
            else
                AddToFringe(fringe, CapA, s.B - (CapA - s.A), s.cost + 1, s.A, s.B, 6);
        }

    }
    return -1;
}

int main(void){
    Dijkstra(3,5,4);
    Dijkstra(5,7,3);
    return 0;
}
