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

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

string s;
int n;

const int MN = 1000111;
struct Node {
    int len, open, close;
    Node(char c) : len(0), open(c == '('), close(c == ')') {}
    Node(int len = 0, int open = 0, int close = 0) : len(len), open(open), close(close) {}

    Node operator + (Node a) {
        int can = min(open, a.close);
        return Node(len + a.len + can,
                open - can + a.open,
                close + a.close - can);
    }
} it[MN * 8];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)
#define mid ((l + r) >> 1)
void build(int i, int l, int r) {
    if (l == r) {
        it[i] = Node(s[l]);
        return ;
    }
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);

    it[i] = it[CT(i)] + it[CP(i)];
}

Node get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return Node();
    if (u <= l && r <= v) return it[i];
    return get(CT(i), l, mid, u, v) + get(CP(i), mid+1, r, u, v);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        n = s.length();
        s = " " + s;
        build(1, 1, n);

        int q; cin >> q;
        while (q--) {
            int u, v; cin >> u >> v;
            Node cur = get(1, 1, n, u, v);
            cout << 2 * cur.len << "\n";
        }
    }
    return 0;
}
