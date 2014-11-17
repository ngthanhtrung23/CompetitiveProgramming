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

const int MN = 200111;
struct Query {
    int typ;
    int u;
    long long val;
} queries[MN];
int n, q, s;
long long h[MN], c[MN];

long long bitSum[MN], bitCnt[MN];

#define _(X) ((X) & (-(X)))
void update(int u, long long val) {
    while (u < MN) {
        bitCnt[u] += 1;
        bitSum[u] += val;
        u += _(u);
    }
}

void erase(int u, long long val) {
    while (u < MN) {
        bitCnt[u] -= 1;
        bitSum[u] -= val;
        u += _(u);
    }
}

long long getCnt(int u) {
    long long res = 0;
    while (u > 0) {
        res += bitCnt[u];
        u -= _(u);
    }
    return res;
}

long long getSum(int u) {
    long long res = 0;
    while (u > 0) {
        res += bitSum[u];
        u -= _(u);
    }
    return res;
}

long long get(int u) {
    return getCnt(u) * c[u+1] - getSum(u);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> q) {
        FOR(i,1,n) cin >> h[i];
        FOR(i,1,q) {
            cin >> queries[i].typ;
            if (queries[i].typ == 1) cin >> queries[i].u >> queries[i].val;
            else cin >> queries[i].val;
        }
        s = 0;
        FOR(i,1,n) c[++s] = h[i];
        FOR(i,1,q) if (queries[i].typ == 1) c[++s] = queries[i].val;

        sort(c+1, c+s+1);
        s = unique(c+1, c+s+1) - c - 1;
        // PR(c, s);

        FOR(i,1,n) h[i] = lower_bound(c+1, c+s+1, h[i]) - c;
        FOR(i,1,q) if (queries[i].typ == 1) {
            queries[i].val = lower_bound(c+1, c+s+1, queries[i].val) - c;
        }

        memset(bitCnt, 0, sizeof bitCnt);
        memset(bitSum, 0, sizeof bitSum);
        FOR(i,1,n) {
            update(h[i], c[h[i]]);
        }

        FOR(i,1,q) {
            if (queries[i].typ == 1) {
                int u = queries[i].u;
                erase(h[u], c[h[u]]);
                h[u] = queries[i].val;
                update(h[u], c[h[u]]);
            }
            else {
                int l = 0, r = s - 1, res = s;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (get(mid) >= queries[i].val) {
                        res = mid;
                        r = mid - 1;
                    }
                    else l = mid + 1;
                }
                // DEBUG(res);
                double ans = c[res] + (queries[i].val - (getCnt(res) * c[res] - getSum(res))) / (double) getCnt(res);
                cout << ans << "\n";
            }
        }
    }
    return 0;
}
