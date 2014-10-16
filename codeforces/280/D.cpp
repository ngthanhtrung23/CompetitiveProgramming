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

const int MN = 100111;

struct Val {
    int u, v, val;
    Val(int u = 0, int v = 0, int val = 0) : u(u), v(v), val(val) {}

    Val operator + (Val a) {
        return Val(min(u, a.u), max(v, a.v), val + a.val);
    }
    bool operator < (const Val &a) const { return val < a.val; }
    bool operator > (const Val &a) const { return val > a.val; }

    void neg() { val = -val; }
};

struct F {
    Val left, right, gss;
    void neg() { left.neg(); right.neg(); gss.neg(); }
    F(int u = 0, int v = 0, int val = 0) : left(u, v, val), right(u, v, val), gss(u, v, val) {}
};

struct Node {
    F nn, ln;
    bool negated;
    Val sum;

    void neg() {
        negated = !negated;
        nn.neg();
        ln.neg();
        sum.neg();

        swap(nn, ln);
    }
} it[MN * 4];

#define CT(X) ((X)<<1)
#define CP(X) (CT(X) + 1)

int a[MN], n;

template<typename T> T MIN(T a, T b) { return (a < b) ? a : b; }
template<typename T> T MAX(T a, T b) { return (a > b) ? a : b; }

void updateNode(int i) {
    it[i].sum = it[CT(i)].sum + it[CP(i)].sum;
    it[i].nn.left = MIN(it[CT(i)].nn.left, it[CT(i)].sum + it[CP(i)].nn.left);
    it[i].nn.right = MIN(it[CP(i)].nn.right, it[CP(i)].sum + it[CT(i)].nn.right);
    it[i].nn.gss = MIN(
            MIN(it[CT(i)].nn.gss, it[CP(i)].nn.gss),
            it[CT(i)].nn.right + it[CP(i)].nn.left
    );

    it[i].ln.left = MAX(it[CT(i)].ln.left, it[CT(i)].sum + it[CP(i)].ln.left);
    it[i].ln.right = MAX(it[CP(i)].ln.right, it[CP(i)].sum + it[CT(i)].ln.right);
    it[i].ln.gss = MAX(
            MAX(it[CT(i)].ln.gss, it[CP(i)].ln.gss),
            it[CT(i)].ln.right + it[CP(i)].ln.left
    );
}

void refine(int i) {
    if (it[i].negated) {
        it[CT(i)].neg();
        it[CP(i)].neg();

        it[i].negated = false;
    }
}

void init(int i, int l, int r) {
    it[i].negated = false;
    if (l == r) {
        it[i].nn = F(l, l, a[l]);
        it[i].ln = F(l, l, a[l]);
        it[i].sum = Val(l, l, a[l]);
        return;
    }
    int mid = (l + r) >> 1;
    init(CT(i), l, mid);
    init(CP(i), mid+1, r);
    updateNode(i);
}

void update(int i, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (r == l) {
        it[i].nn = F(u, u, val);
        it[i].ln = F(u, u, val);
        it[i].sum = Val(u, u, val);
        return ;
    }
    refine(i);

    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, val);
    update(CP(i), mid+1, r, u, val);
    updateNode(i);
}

void reverse(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].neg();
        return ;
    }
    refine(i);
    int mid = (l + r) >> 1;
    reverse(CT(i), l, mid, u, v);
    reverse(CP(i), mid+1, r, u, v);
    updateNode(i);
}

vector<Node> nodes;

void visit(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        nodes.push_back(it[i]);
        return;
    }
    int mid = (l + r) >> 1;
    refine(i);
    visit(CT(i), l, mid, u, v);
    visit(CP(i), mid+1, r, u, v);
    updateNode(i);
}

Val get(int u, int v) {
    nodes.clear();
    visit(1, 1, n, u, v);
    Val res = Val(0, 0, 0), maxRight = Val(0, 0, 0);

    REP(i,nodes.size()) {
        res = MAX(res, nodes[i].ln.gss);
        res = MAX(res, maxRight + nodes[i].ln.left);

        maxRight = MAX(nodes[i].ln.right, maxRight + nodes[i].sum);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
//    freopen("input.txt", "r", stdin);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        init(1, 1, n);

        int q; cin >> q;
        while (q--) {
            int typ; cin >> typ;
            if (typ == 0) {
                int u, val; cin >> u >> val;
                update(1, 1, n, u, val);
            } else {
                int u, v, k; cin >> u >> v >> k;
                vector< pair<int,int> > reversed;

                int res = 0, all = 0;
                while (k--) {
                    Val cur = get(u, v);
                    all += cur.val;
                    res = max(res, all);

                    reverse(1, 1, n, cur.u, cur.v);
                    reversed.push_back(make_pair(cur.u, cur.v));
                }

                cout << res << endl;
                REP(i,reversed.size()) {
                    reverse(1, 1, n, reversed[i].first, reversed[i].second);
                }
            }
        }
    }
    return 0;
}
