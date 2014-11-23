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
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

long long a[2], b[2];
map< long long, int > d[2];
map< long long, pair<long long, long long> > trace[2];
queue< long long > q;

void add(long long x, long long s, int turn, int div) {
    if (!d[turn].count(x)) {
        q.push(x);
        d[turn][x] = d[turn][s] + 1;
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> a[0] >> b[0] >> a[1] >> b[1]) {
        REP(turn,2) {
            d[turn].clear();

            long long s = a[turn] * b[turn];
            d[turn][s] = 0;
            trace[turn][s] = make_pair(a[turn], b[turn]);
            q.push(s);
            while (!q.empty()) {
                long long s = q.front(); q.pop();
                
                if (s % 3 == 0) {
                    add(s / 3 * 2, s, turn, 3);
                    pair<long long, long long> next = trace[turn][s];
                    if (next.first % 3 == 0) next.first = next.first / 3 * 2;
                    else next.second = next.second / 3 * 2;
                    trace[turn][s/3*2] = next;
                }
                if (s % 2 == 0) {
                    add(s / 2, s, turn, 2);
                    pair<long long, long long> next = trace[turn][s];
                    if (next.first % 2 == 0) next.first /= 2;
                    else next.second /= 2;
                    trace[turn][s/2] = next;
                }
            }
        }
        const long long inf = 1000111000;
        long long best = inf, save = -1;
        for(auto cur : d[0]) if (d[1].count(cur.first)) {
            long long f = cur.second + d[1][cur.first];
            if (f < best) {
                best = f;
                save = cur.first;
            }
        }
        if (best == inf) {
            cout << -1 << endl;
            continue;
        }
        cout << best << endl;
        cout << trace[0][save].first << ' ' << trace[0][save].second << endl;
        cout << trace[1][save].first << ' ' << trace[1][save].second << endl;
    }
    return 0;
}
