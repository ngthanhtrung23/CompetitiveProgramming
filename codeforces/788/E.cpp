
#include <sstream>
#include <fstream>
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
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define PI (2 * acos((double)0))
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 100111;
const int MOD = 1e9 + 7;

int n, a[MN], c[MN], nc;
int bit[MN], left[MN], right[MN];

void update(int u, int val) {
    for(; u < MN; u += u & -u)
        bit[u] += val;
}
int get(int u) {
    int res = 0;
    for(; u > 0; u -= u & -u)
        res += bit[u];
    return res;
}

void RR() {
    FOR(i,1,n) c[i] = a[i];
    sort(c+1, c+n+1);
    nc = unique(c+1, c+n+1) - c - 1;

    FOR(i,1,n) a[i] = lower_bound(c+1, c+nc+1, a[i]) - c;
}

struct NodeVal {
    int f[4][4];
};

NodeVal operator + (const NodeVal& a, const NodeVal& b) {
    NodeVal res;
    REP(i,4) FOR(j,i,3) {
        res.f[i][j] = 0;
        FOR(k,i,j)
            res.f[i][j] = (res.f[i][j] + a.f[i][k] * b.f[k][j]) % MOD;
    }
    return res;
}

struct Node {
    NodeVal val;
    Node* left, *right;

    Node() {
        memset(val.f, 0, sizeof val.f);
        left = right = 0;
    }
};

struct Value {
    vector<int> index;
    Node* it;

    void init() {
        it = build(1, SZ(index) - 1);
    }

    Node* build(int l, int r) {
        if (l == r) {
            Node* res = new Node();
            REP(t,4) res->val.f[t][t] = 1;
            res->val.f[0][1] = left[index[l]];
            res->val.f[1][2] = 1;
            res->val.f[2][3] = right[index[l]];
            return res;
        }
        int mid = (l + r) >> 1;
        Node* L = build(l, mid);
        Node* R = build(mid+1, r);

        Node* res = new Node();
        res->val = L->val + R->val;
        res->left = L;
        res->right = R;
        return res;
    }

    void update(Node* p, int l, int r, int u, bool enable) {
        if (u < l || r < u) return ;
        if (l == r) {
            if (enable) {
                p->val.f[0][1] = left[index[l]];
                p->val.f[1][2] = 1;
                p->val.f[2][3] = right[index[l]];
            } else {
                p->val.f[0][1] = 0;
                p->val.f[1][2] = 0;
                p->val.f[2][3] = 0;
            }
            return ;
        }
        int mid = (l + r) >> 1;
        update(p->left, l, mid, u, enable);
        update(p->right, mid+1, r, u, enable);

        p->val = p->left->val + p->right->val;
    }

    int getIndex(int pos) {
        return lower_bound(index.begin(), index.end(), pos) - index.begin();
    }

    void disable(int pos) {
        update(it, 1, SZ(index) - 1, getIndex(pos), false);
    }

    void enable(int pos) {
        update(it, 1, SZ(index) - 1, getIndex(pos), true);
    }
} all[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (GI(n) == 1) {
        FOR(i,1,n) GI(a[i]);
        RR();

        // init left[i] = count(j, j < i and a(j) <= a(i))
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            left[i] = get(a[i]);
            update(a[i], +1);
        }
        
        // init right[i] = count(j, j > i and a(j) <= a(i))
        memset(bit, 0, sizeof bit);
        FORD(i,n,1) {
            right[i] = get(a[i]);
            update(a[i], +1);
        }

        // init all[i]
        FOR(i,1,nc) {
            all[i].index.clear();
            all[i].index.push_back(0);  // I want 1-based index.
            all[i].it = 0;
        }

        FOR(i,1,n) {
            all[a[i]].index.push_back(i);
        }

        int res = 0;
        FOR(i,1,nc) {
            all[i].init();
            res = (res + all[i].it->val.f[0][3]) % MOD;
        }

        int q; GI(q);
        while (q--) {
            int typ; GI(typ);
            int index; GI(index);

            res = (res - all[a[index]].it->val.f[0][3] + MOD) % MOD;
            if (res < 0) res += MOD;
            if (typ == 1) {
                all[a[index]].disable(index);
            } else {
                all[a[index]].enable(index);
            }
            res = (res + all[a[index]].it->val.f[0][3]) % MOD;

            printf("%lld\n", res);
        }
    }
    return 0;
}
