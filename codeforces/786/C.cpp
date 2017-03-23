
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
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)
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

struct Node {
    Node* left;
    Node* right;
    int sum;
};

Node* createNode() {
    Node* res = new Node();
    res->left = res->right = 0;
    res->sum = 0;
    return res;
}

Node* build(int l, int r) {
    Node* res = createNode();
    if (l == r) return res;
    int mid = (l + r) >> 1;
    res->left = build(l, mid);
    res->right = build(mid+1, r);

    return res;
}

Node* update(Node* old, int l, int r, int u, int val) {
    if (u < l || r < u) return old;

    if (l == r) {
        Node* res = createNode();
        res->sum = old->sum + val;
        return res;
    }

    int mid = (l + r) >> 1;
    Node* res = createNode();
    res->left = update(old->left, l, mid, u, val);
    res->right = update(old->right, mid+1, r, u, val);

    res->sum = res->left->sum + res->right->sum;

    return res;
}

int getKth(Node* cur, int l, int r, int k) {
    if (l == r) return l;

    int mid = (l + r) >> 1;
    if (cur->left->sum >= k) return getKth(cur->left, l, mid, k);
    else return getKth(cur->right, mid+1, r, k - cur->left->sum);
}

const int MN = 100111;
int n, a[MN], cur[MN], next[MN];
Node* ver[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (GI(n) == 1) {
        FOR(i,1,n) GI(a[i]);
        FOR(i,1,n) cur[i] = n+1;

        ver[n+1] = build(1, n);
        FORD(i,n,1) {
            next[i] = cur[a[i]];
            cur[a[i]] = i;

            ver[i] = update(ver[i+1], 1, n, i, +1);
            if (next[i] <= n) ver[i] = update(ver[i], 1, n, next[i], -1);
        }

        FOR(k,1,n) {
            int i = 1, cnt = 0;
            while (i <= n) {
                ++cnt;

                int j;
                if (ver[i]->sum <= k) j = n+1;
                else j = getKth(ver[i], 1, n, k + 1);
                i = j;
            }
            printf("%lld ", cnt);
        }
        puts("");
    }
    return 0;
}
