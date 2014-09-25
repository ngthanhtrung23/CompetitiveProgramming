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
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;
#define next next_

int c, n, a;
int id[MN], access[MN], next[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> c >> n >> a) {
        memset(id, -1, sizeof id);
        FOR(i,1,a) cin >> access[i];

        FORD(i,a,1) {
            if (id[access[i]] < 0) next[i] = a+1;
            else next[i] = id[access[i]];

            id[access[i]] = i;
        }

        // PR(next, a);

        set< pair<int,int> > cached;
        set< int > good;
        int res = 0;
        FOR(i,1,a) {
            int u = access[i];
            if (good.find(u) == good.end()) {
                if (good.size() == c) {
                    int v = cached.begin()->second;
                    cached.erase(cached.begin());
                    good.erase(v);
                }
                ++res;
                cached.insert(make_pair(-next[i], u));
                good.insert(u);
            } else {
                cached.erase(make_pair(-i, u));
                cached.insert(make_pair(-next[i], u));
            }

            // for(__typeof(cached.begin()) it = cached.begin(); it != cached.end(); ++it) {
            //     cout << it->first << ' ' << it->second << "    ";
            // }
            // cout << endl;
            // for(__typeof(good.begin()) it = good.begin(); it != good.end(); ++it) {
            //     cout << *it << ' ';
            // }
            // cout << endl;
        }
        cout << res << endl;
    }
    return 0;
}
