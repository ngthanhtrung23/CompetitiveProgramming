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
template<typename T> T MAX(T a, T b) { if (b < a) return a; return b; }

using namespace std;

const int MN = 100111;

#define prev prev_
struct Node {
    int val, trace;

    Node(int val = 0, int trace = -1) : val(val), trace(trace) {}
} it[MN * 8];

bool operator < (const Node &a, const Node &b) {
    return a.val < b.val;
}

int n, s, d;
int f[MN], prev[MN];
long long h[MN], c[MN];

void RR() {
    FOR(i,1,n) c[i] = h[i];
    sort(c+1, c+n+1);
    s = unique(c+1, c+n+1) - c - 1;

}

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

Node get(int i, int l, int r, long long u, long long v) {
    if (u > v) return Node();
    if (v < c[l] || c[r] < u) return Node(0, -1);
    if (u <= c[l] && c[r] <= v) return it[i];

    int mid = (l + r) >> 1;
    return MAX(get(CT(i), l, mid, u, v), get(CP(i), mid+1, r, u, v));
}

void update(int i, int l, int r, long long h, const Node &cur) {
    if (h < c[l] || c[r] < h) return ;

    if (l == r) {
        it[i] = MAX(it[i], cur);
        return ;
    }

    int mid = (l + r) >> 1;
    update(CT(i), l, mid, h, cur);
    update(CP(i), mid+1, r, h, cur);

    it[i] = max(it[CT(i)], it[CP(i)]);
}

void trace(int id) {
    if (id <= 0) return ;
    trace(prev[id]);
    cout << id << ' ';
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> d) {
        FOR(i,1,n) cin >> h[i];
        RR();

        memset(it, 0, sizeof it);

        int res = 0, last = -1;
        FOR(i,1,n) {
            Node best = MAX(get(1, 1, s, 1, h[i] - d), get(1, 1, s, h[i] + d, 1000111000111000LL));

            Node cur = Node(best.val + 1, i);
            prev[i] = best.trace;

            update(1, 1, s, h[i], cur);

            if (cur.val > res) {
                res = cur.val;
                last = i;
            }
        }

        cout << res << endl;
        trace(last);
        cout << endl;
    }
    return 0;
}
