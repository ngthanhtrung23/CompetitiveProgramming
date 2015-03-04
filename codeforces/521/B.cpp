
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;
const int MN = 100111;
const ll MOD = 1e9 + 9;

map< pair<int,int>, int> support;
set< pair<int, pair<int,int> > > all;
map< pair<int,int>,int > exist;
pair<int,int> a[MN];
int n;

int isGood(int x0, int y0) {
    if (!exist.count(make_pair(x0, y0))) return -1;
    FOR(x,x0-1,x0+1) {
        if (exist.count(make_pair(x, y0+1))
                && support[make_pair(x, y0+1)] == 1) {
            return -1;
        }
    }
    return exist[make_pair(x0, y0)];
}

int main() {
    while (scanf("%d", &n) == 1) {
        support.clear();
        exist.clear();
        all.clear();
        REP(i,n) {
            scanf("%d%d", &a[i].first, &a[i].second);
            exist[a[i]] = i;
        }
        REP(i,n) {
            if (a[i].second == 0) support[a[i]] = MN;
            else {
                int cnt = 0;
                FOR(x,a[i].first-1,a[i].first+1)
                    if (exist.count(make_pair(x, a[i].second-1))) {
                        ++cnt;
                    }
                support[a[i]] = cnt;
            }
//            cout << a[i].first << ' ' << a[i].second << ' ' << support[a[i]] << endl;
        }
        REP(i,n) {
            if (isGood(a[i].first, a[i].second) == i) {
                all.insert(make_pair(i, a[i]));
//                DEBUG(i);
            }
        }

        ll res = 0;
        REP(turn,n) {
            ll cur = 0;
            int x, y;
            if (turn % 2 == 0) {
                auto it = all.end(); --it;
                cur = it->first;
                x = it->second.first;
                y = it->second.second;
                all.erase(it);
            }
            else {
                auto it = all.begin();
                cur = it->first;
                x = it->second.first;
                y = it->second.second;
                all.erase(it);
            }
            exist.erase(make_pair(x, y));
//            DEBUG(cur);

            // Support can become available
            FOR(xx,x-1,x+1) {
                int t = isGood(xx, y-1);
                if (t >= 0) {
                    all.insert(make_pair(t, make_pair(xx, y-1)));
                }
            }

            // Support count needs to be changed
            FOR(xx,x-1,x+1) {
                if (exist.count(make_pair(xx, y+1))) {
                    support[make_pair(xx, y+1)] -= 1;
                }
            }

            // Neighbours can become unavailable
            FOR(xx,x-2,x+2) {
                if (exist.count(make_pair(xx, y))) {
                    int t = exist[make_pair(xx, y)];
                    if (isGood(xx, y) < 0) {
                        all.erase(make_pair(t, make_pair(xx, y)));
                    }
                }
            }

            res = (res * n + cur) % MOD;
        }
        cout << res << endl;
    }
    return 0;
}

