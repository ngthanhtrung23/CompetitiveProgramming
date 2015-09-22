
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const ll MOD = 1e9 + 9;
struct Hash {
    ll x, y;

    Hash() {}
    Hash(ll x, ll y) : x(x), y(y) {}

    Hash operator + (const Hash& a) {
        return Hash(x+a.x, (y+a.y) % MOD);
    }
    Hash operator - (const Hash& a) {
        return Hash(x-a.x, (y-a.y+MOD) % MOD);
    }
    Hash operator * (ll k) {
        return Hash(x*k, y*k % MOD);
    }
    Hash operator * (const Hash& a) {
        return Hash(x*a.x, y*a.y % MOD);
    }

    bool operator == (const Hash& a) {
        return x == a.x && y == a.y;
    }
};

const int MN = 100111;
int a[MN];
Hash p[MN];

struct Node {
    Node* left, *right;
    Hash val;
} *it, *pre[11];

Node* build(int i, int l, int r, int val) {
    if (l == r) {
        Node* res = new Node();
        res->left = res->right = 0;
        
        if (val == -1) res->val = p[l] * a[l];
        else res->val = p[l] * val;
        return res;
    }
    int mid = (l + r) >> 1;

    Node* res = new Node();
    res->left = build(i<<1, l, mid, val);
    res->right = build(i<<1|1, mid+1, r, val);

    res->val = res->left->val + res->right->val;
    return res;
}

Node* update(Node* it, int l, int r, int u, int v, Node* pre) {
    if (v < l || r < u) return it;
    if (u <= l && r <= v) {
        it = pre;
        return pre;
    }

    int mid = (l + r) >> 1;

    Node *res = new Node;
    res->left = update(it->left, l, mid, u, v, pre->left);
    res->right = update(it->right, mid+1, r, u, v, pre->right);

    res->val = res->left->val + res->right->val;
    return res;
}

Hash get(Node* it, int l, int r, int u, int v) {
    if (v < l || r < u) return Hash(0, 0);
    if (u <= l && r <= v) return it->val;

    int mid = (l + r) >> 1;
    return get(it->left, l, mid, u, v) + get(it->right, mid+1, r, u, v);
}

char tmp[MN];
int main() {
    ios :: sync_with_stdio(false);
    int n, m, k;
    p[0] = Hash(1,1);
    FOR(i,1,MN-1) p[i] = p[i-1] * 11;

    while (scanf("%d%d%d\n", &n, &m, &k) == 3) {

        int q = m + k;
        gets(tmp);
        FOR(i,1,n) a[i] = tmp[i-1] - '0' + 1;

//        PR(a, n);

        it = build(1,1,n,-1);
        FOR(x,1,10) pre[x] = build(1, 1, n, x);
        

        while (q--) {
            int typ, u, v, val;
            scanf("%d%d%d%d", &typ, &u, &v, &val);
            if (typ == 1) {
                ++val;
                it = update(it, 1, n, u, v, pre[val]);
            }
            else {
                if (val == v - u + 1) puts("YES");
                else {
                    Hash x = get(it, 1, n, u, v-val);
                    Hash y = get(it, 1, n, u+val, v);
                    if (x * p[val] == y) puts("YES");
                    else puts("NO");
                }
            }
        }
    }
}
