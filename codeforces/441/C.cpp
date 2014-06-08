#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

vector< pair<int,int> > x;
vector< pair<int,int> > res[1000111];

int main() {
    ios :: sync_with_stdio(false);
    int m, n, k;
    while (cin >> m >> n >> k) {
        x.clear();
        FOR(i,1,m) {
            if (i % 2 == 1) {
                FOR(j,1,n) x.push_back(make_pair(i,j));
            }
            else {
                FORD(j,n,1) x.push_back(make_pair(i,j));
            }
        }
        FOR(i,1,k) res[i].clear();

        REP(i,x.size())
            res[min(i/2+1,k)].push_back(x[i]);

        FOR(i,1,k) {
            cout << res[i].size();
            REP(j,res[i].size()) cout << ' ' << res[i][j].first << ' ' << res[i][j].second;
            cout << endl;
        }
    }
    return 0;
}
