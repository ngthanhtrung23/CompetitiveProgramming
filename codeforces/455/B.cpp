#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 200111;

struct Node {
    int next[30];
    int win, lose;
} nodes[MN];

int n, k, nnodes;

void dfs(int u) {
    nodes[u].win = false;
    nodes[u].lose = false;

    bool hasChild = false;
    REP(c,30) {
        int v = nodes[u].next[c];
        if (!v) continue;

        dfs(v);
        hasChild = true;

        nodes[u].win |= !nodes[v].win;
        nodes[u].lose |= !nodes[v].lose;
    }

    if (!hasChild) nodes[u].lose = true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        memset(nodes, 0, sizeof nodes);
        nnodes = 1;
        FOR(i,1,n) {
            string tmp; cin >> tmp;
            int p = 1;
            REP(i,tmp.length()) {
                char c = tmp[i] - 'a';
                if (!nodes[p].next[c]) {
                    ++nnodes;
                    nodes[p].next[c] = nnodes;
                }
                p = nodes[p].next[c];
            }
        }

        dfs(1);
        
        if (!nodes[1].win) cout << "Second";
        else if (nodes[1].win && nodes[1].lose) cout << "First";
        else if (k % 2 == 1) cout << "First";
        else cout << "Second";
        cout << endl;
    }
    return 0;
}
