#include <sstream>
#include <iomanip>
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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

int n, m, a[222];
vector<int> cur;
vector< pair<int,int> > res;

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        memset(a, 0, sizeof a);
        int now = 0;
        FOR(i,1,m) {
            int k; scanf("%d", &k);
            while (k--) {
                int u; scanf("%d", &u);
                a[u] = ++now;
            }
        }
        res.clear();
        FORD(i,n,1) if (a[i]) {
            int j = 0;
            FOR(j,1,i-1) if (a[j] == 0) {
                res.PB(MP(i,j));
                a[j] = a[i];
                a[i] = 0;
                break;
            }
        }
        FOR(i,1,n) {
            if (!a[i]) break;
            if (a[i] == i) continue;
            cur.clear();
            int u = a[i];
            cur.PB(i);
            while (u != i) {
                cur.PB(u);
                u = a[u];
            }
            // PR0(cur, cur.size());
            res.PB(MP(cur[cur.size()-1], n));
            a[n] = a[cur.size()-1];

            FORD(i,cur.size()-2,0) {
                res.PB(MP(cur[i], cur[i+1]));
                a[cur[i+1]] = a[cur[i]];
            }
            res.PB(MP(n, cur[0]));
            a[cur[0]] = a[n];
            a[n] = 0;
        }
        printf("%d\n", res.size());
        REP(i,res.size()) printf("%d %d\n", res[i].F, res[i].S);
    }
    return 0;
}
