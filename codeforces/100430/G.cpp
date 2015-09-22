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

const int MN = 100111;
int n;
int a[MN];
vector< pair< pair<int,int>, int > > res;

void add(int u, int v, int k) {
    res.push_back(make_pair(make_pair(min(u, v), max(u, v)), k));
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    while (cin >> n) {
        set< pair<int,int> > all;
        all.clear();
        FOR(i,1,n) {
            cin >> a[i];
            all.insert(make_pair(i, a[i]));
        }
        res.clear();

        while (all.size() > 1) {
            pair<int,int> x = *all.begin(); all.erase(all.begin());
            pair<int,int> y = *all.begin(); all.erase(all.begin());

            int can = min(x.second, y.second);

            res.push_back(make_pair(make_pair(x.first, y.first), can));
            if (x.second > can) {
                all.insert(make_pair(x.first, x.second - can));
            }
            if (y.second > can) {
                all.insert(make_pair(y.first, y.second - can));
            }
        }

        FORD(i,res.size()-1,0) {
            int can = res[i].second;
            if (all.size() == 1 && all.begin()->second >= 2
                    && res[i].first.first != all.begin()->first
                    && res[i].first.second != all.begin()->first) {
                int now = min(can, (int) all.begin()->second / 2);
                res[i].second -= now;

                add(res[i].first.first, all.begin()->first, now);
                add(res[i].first.second, all.begin()->first, now);

                pair<int,int> t = *all.begin(); all.erase(all.begin());
                t.second -= 2 * now;
                all.insert(t);
            }
        }
        sort(res.begin(), res.end());

        map< pair<int,int>, int > cnt;
        REP(i,res.size()) if (res[i].second) {
            cnt[res[i].first] += res[i].second;
        }
        cout << cnt.size() << endl;
        for(__typeof(cnt.begin()) it = cnt.begin(); it != cnt.end(); ++it)
            cout << it->first.first << ' ' << it->first.second << ' ' << it->second << "\n";
    }
    return 0;
}