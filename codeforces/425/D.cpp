#include <bits/stdc++.h>
#include <tr1/unordered_set>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;
using namespace std::tr1;

const int MN = 100111;

int n;
pair<int,int> a[MN];
unordered_set<int> hasX[MN], hasY[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,0,100000) {
            hasX[i].clear();
            hasY[i].clear();
        }
        FOR(i,1,n) {
            cin >> a[i].first >> a[i].second;
        }
        sort(a+1, a+n+1);

        int res = 0;
        FOR(i,1,n) {
            int x = a[i].first, y = a[i].second;
            if (hasX[x].size() < hasY[y].size()) {
                for(__typeof(hasX[x].begin()) it = hasX[x].begin(); it != hasX[x].end(); ++it) {
                    int y2 = *it;
                    int len = y - y2;

                    if (x - len >= 0
                            && hasX[x-len].count(y)
                            && hasX[x-len].count(y2))
                        ++res;
                }
            }
            else {
                for(__typeof(hasY[y].begin()) it = hasY[y].begin(); it != hasY[y].end(); ++it) {
                    int x2 = *it;
                    int len = x - x2;

                    if (y - len >= 0
                            && hasY[y-len].count(x)
                            && hasY[y-len].count(x2))
                        ++res;
                }
            }
            hasX[x].insert(y);
            hasY[y].insert(x);
        }
        cout << res << endl;
    }
    return 0;
}
