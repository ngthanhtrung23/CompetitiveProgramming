
#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

struct Station {
    int x, r, f;

    void read() {
        GI(x);
        GI(r);
        GI(f);
    }
} a[100111];

bool operator < (const Station& a, const Station& b) {
    return a.r > b.r;
}

const int INF = 1000111000;

struct Node {
    Node* left, *right;
    int sum;
} *it[10111], *sentinel;

Node* createNode(int val = 0) {
    Node* res = new Node();
    res->left = res->right = sentinel;
    res->sum = val;
    return res;
}

int get(Node* cur, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return cur->sum;

    int mid = (l + r) >> 1;
    int res = 0;
    if (cur->left != sentinel) res += get(cur->left, l, mid, u, v);
    if (cur->right != sentinel) res += get(cur->right, mid+1, r, u, v);
    return res;
}

void update(Node* cur, int l, int r, int u) {
    if (u < l || r < u) return ;

    cur->sum++;
    if (l == r) return ;

    int mid = (l + r) >> 1;
    if (u <= mid) {
        if (cur->left == sentinel) cur->left = createNode();
        update(cur->left, l, mid, u);
    }
    else {
        if (cur->right == sentinel) cur->right = createNode();
        update(cur->right, mid+1, r, u);
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, k;

    sentinel = new Node();
    sentinel->sum = 0;
    sentinel->left = sentinel->right = sentinel;

    while (GI(n) == 1) {
        GI(k);
        FOR(i,1,n) {
            a[i].read();
        }
        sort(a+1, a+n+1);
        FOR(i,1,10000) it[i] = createNode();
        int res = 0;
        FOR(i,1,n) {
            FOR(y, max(a[i].f - k, 1LL), min(a[i].f + k, 10000LL)) {
                int minx = a[i].x - a[i].r;
                int maxx = a[i].x + a[i].r;

                res += get(it[y], 1, INF, minx, maxx);
            }
            update(it[a[i].f], 1, INF, a[i].x);
        }
        cout << res << '\n';
    }
}
