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

#define sqr(x) ((x) * (x))
using namespace std;

const int MAXN = 100100;

struct Hull {
    long long a[MAXN], b[MAXN];
    double x[MAXN];
    int head, tail;

    Hull(): head(1), tail(0) {}

    long long get(long long xQuery) {
        if (head > tail) return 0;
        while (head < tail && x[head + 1] <= xQuery) head++;
        x[head] = xQuery;
        return a[head] * xQuery + b[head];
    }

    void add(long long aNew, long long bNew) {
        double xNew = -1e18;
        while (head <= tail) {
            if (aNew == a[tail]) return;
            xNew = 1.0 * (b[tail] - bNew) / (aNew - a[tail]);
            if (head == tail || xNew >= x[tail]) break;
            tail--;
        }
        a[++tail] = aNew;
        b[tail] = bNew;
        x[tail] = xNew;
    }
};


const int MN = 100111;

int n, m, nFeed;
long long d[MN], p[MN], h[MN], a[MN], s[MN], t[MN];
long long f[111][MN];

int main() {
    while (cin >> n >> m >> nFeed) {
        FOR(i,2,n) {
            cin >> d[i];
            p[i] = p[i-1] + d[i];
        }
        FOR(i,1,m) {
            cin >> h[i] >> t[i];
            a[i] = t[i] - p[h[i]];
        }
        sort(a+1, a+m+1);
        FOR(i,1,m) s[i] = s[i-1] + a[i];

        // PR(a, m);

        FOR(i,1,nFeed) {
            Hull hull;
            FOR(j,1,m) {
                f[i][j] = hull.get(a[j]) + a[j] * j - s[j];
                if (i > 1) hull.add(-j, f[i-1][j] + s[j]);
            }
            // PR(f[i], m);
        }
        long long res = f[1][m];
        FOR(i,1,nFeed) res = min(res, f[i][m]);
        cout << res << endl;
    }
}
