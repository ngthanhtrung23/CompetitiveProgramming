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

struct Node {
    int gcd, min, minCount;

    Node(int gcd = 0, int min = 0, int minCount = 0) : gcd(gcd), min(min), minCount(minCount) {}
} it[MN * 8];

int n, a[MN];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

Node combine(const Node &left, const Node &right) {
    Node res;
    res.gcd = __gcd(left.gcd, right.gcd);
    res.min = min(left.min, right.min);
    res.minCount = 0;
    if (left.min == res.min) res.minCount += left.minCount;
    if (right.min == res.min) res.minCount += right.minCount;
    return res;
}

void init(int i, int l, int r) {
    if (l == r) {
        it[i] = Node(a[l], a[l], 1);
        return ;
    }
    int mid = (l + r) >> 1;
    init(CT(i), l, mid);
    init(CP(i), mid+1, r);

    it[i] = combine(it[CT(i)], it[CP(i)]);
}

const int oo = 1000111000;

Node get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return Node(0, oo, 0);
    if (u <= l && r <= v) return it[i];

    int mid = (l + r) >> 1;
    return combine( get(CT(i), l, mid, u, v), get(CP(i), mid+1, r, u, v));
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        init(1, 1, n);

        int q; cin >> q;
        while (q--) {
            int u, v; cin >> u >> v;
            Node cur = get(1, 1, n, u, v);

            if (cur.gcd % cur.min == 0) {
                cout << (v - u + 1) - cur.minCount << "\n";
            }
            else cout << (v - u + 1) << endl;
        }
    }
    return 0;
}
