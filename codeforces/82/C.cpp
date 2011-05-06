#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>
#include <sstream>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);

int n, a[5011], fat[5011], up[5011], space[5011];
vector< pair<int,int> > x[2];
vector< pair<int,int> > ke[5011];
map<int,int> m;

void dfs(int u, int fu) {
    REP(i,ke[u].size()) {
        int v = ke[u][i].F, c = ke[u][i].S;
        if (v == fu) continue;
        
        fat[v] = u;
        up[v] = c;
        dfs(v, u);
    }
}

int t[5011];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    FOR(i,1,n) {
        scanf("%d", &a[i]);
        m[a[i]] = i;
    }
    FOR(i,2,n) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        ke[u].PB(MP(v,c));
        ke[v].PB(MP(u,c));
    }
    dfs(1, -1);
    
    t[1] = 0;
    FOR(i,2,n) x[0].PB(MP(a[i], i));
    int now = 0, time = 0;
    
    while (x[now].size()) {
        time++;
//        if (time % 100 == 0) cerr << time << " " << x[now].size() << endl;
        sort(x[now].begin(), x[now].end());
        
//        REP(i, x[now].size()) cout << x[now][i].F << ' ' << x[now][i].S << "    "; cout << endl;
        
        x[1-now].clear();
        
        FOR(i,1,n) space[i] = up[i];
        
        REP(i,x[now].size()) {
            int ai = x[now][i].F, pos = x[now][i].S;
//            cout << ai << ' ' << pos << ' ' << space[pos] << endl;
            if (space[pos]) {
                space[pos]--;
                if (fat[pos] == 1) t[m[ai]] = time;
                else x[1-now].PB(MP(ai, fat[pos]));
            }
            else {
                x[1-now].PB(MP(ai, pos));
            }
        }
        
        now = 1 - now;
    }
    FOR(i,1,n) cout << t[i] << ' ';
    return 0;
}
