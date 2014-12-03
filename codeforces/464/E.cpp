#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
const long long MOD[2] = {1000000007, 1000000009};

struct Hash {
    long long x[2];
    Hash(long long a = 0, long long b = 0) {
        x[0] = a;
        x[1] = b;
    }
};

Hash operator + (const Hash &a, const Hash &b) {
    return Hash((a.x[0] + b.x[0]) % MOD[0], (a.x[1] + b.x[1]) % MOD[1]);
}

Hash operator * (const Hash &a, long long k) {
    return Hash((a.x[0] * k) % MOD[0], (a.x[1] * k) % MOD[1]);
}

Hash operator * (const Hash &a, const Hash &b) {
    return Hash((a.x[0] * b.x[0]) % MOD[0], (a.x[1] * b.x[1]) % MOD[1]);
}

bool operator == (const Hash &a, const Hash &b) {
    return a.x[0] == b.x[0] && a.x[1] == b.x[1];
}

Hash p[MN];

struct Node {
    Hash h;
    int firstZero, left, right;
} it[11000111];

int nNode, all0, all1, d[MN];
vector<pair<int,int> > ke[MN];
int n, m, tr[MN];

void up(int x, int leftSize) {
    it[x].h = it[ it[x].right ].h * p[leftSize] + it[ it[x].left ].h;
    if (it[ it[x].left ].firstZero < 0) it[x].firstZero = it[ it[x].right ].firstZero;
    else it[x].firstZero = it[ it[x].left ].firstZero;
}

int createNode(int l, int r, int val) {
    if (l == r) {
        int cur = ++nNode;
        it[cur].h = Hash(val, val);
        it[cur].firstZero = (val ? -1 : l);
        it[cur].left = it[cur].right = 0;
        return cur;
    }
    int mid = (l + r) >> 1;
    int cur = ++nNode;
    it[cur].left = createNode(l, mid, val);
    it[cur].right = createNode(mid+1, r, val);
    up(cur, mid - l + 1);
    return cur;
}

int getFirstZero(int x, int l, int r, int u) {
    if (u < l || r < u) return -1;
    if (l == r) return it[x].firstZero;
    int mid = (l + r) >> 1;
    if (u > mid) return getFirstZero(it[x].right, mid+1, r, u);
    else {
        int res = getFirstZero(it[x].left, l, mid, u);
        if (res < 0) return it[ it[x].right ].firstZero;
        else return res;
    }
}

int setTree(int x, int l, int r, int u, int v, int t) {
    if (v < l || r < u) return x;
    if (u <= l && r <= v) return t;
    int mid = (l + r) >> 1;
    int cur = ++nNode;
    it[cur].left = setTree(it[x].left, l, mid, u, v, it[t].left);
    it[cur].right = setTree(it[x].right, mid+1, r, u, v, it[t].right);
    up(cur, mid - l + 1);
    return cur;
}

int isLower(int x1, int x2, int l, int r) {
    if (it[x1].h == it[x2].h) return 0;
    if (l == r) {
        if (it[x1].h.x[0] < it[x2].h.x[1]) return -1;
        else return 1;
    }
    int mid = (l + r) >> 1;
    if (it[ it[x1].right ].h == it[ it[x2].right ].h) return isLower(it[x1].left, it[x2].left, l, mid);
    else return isLower(it[x1].right, it[x2].right, mid+1, r);
}

struct Comp {
    bool operator () (pair<int,int> u, pair<int,int> v) {
        int t = isLower(u.first, v.first, 1, 100100);
        if (t == 0) return u.second < v.second;
        else if (t < 0) return true;
        else return false;
    }
};

void print(int x, int l, int r) {
    if (l == r) {
        if (it[x].h.x[0]) cout << l << ' ';
        return ;
    }        
    int mid = (l + r) >> 1;
    print(it[x].left, l, mid);
    print(it[x].right, mid+1, r);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    p[0] = Hash(1, 1);
    FOR(i,1,100100) p[i] = p[i-1] * 2;
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v, c; cin >> u >> v >> c;
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
        }
        int start, target; cin >> start >> target;
        nNode = 0;
        all0 = createNode(1, 100100, 0);
        all1 = createNode(1, 100100, 1);
        FOR(i,1,n) d[i] = all1;

        memset(tr, -1, sizeof tr);
        d[start] = all0;
        tr[start] = start;
        set< pair<int,int>, Comp> s;
        s.insert(make_pair(d[start], start));

        while (!s.empty()) {
            int u = s.begin()->second, l = s.begin()->first;
            s.erase(s.begin());
            if (d[u] != l) continue;
//            cout << endl << "d[" << u << "] = "; print(d[u], 1, 100100); cout << endl;

            for(auto cur : ke[u]) {
                int v = cur.first, c = cur.second + 1;
                int x = getFirstZero(d[u], 1, 100100, c);
//                cout << " --> " << v << " 2^" << (c-1) << endl;
//                DEBUG(x);
//                DEBUG(c);
                int tmp = setTree(d[u], 1, 100100, x, x, all1);
                if (c <= x-1) tmp = setTree(tmp, 1, 100100, c, x-1, all0);

//                DEBUG(it[tmp].h.x[0]);

                if (isLower(tmp, d[v], 1, 100100) < 0) {
//                    DEBUG(v);
                    d[v] = tmp;
                    tr[v] = u;
                    s.insert(make_pair(d[v], v));
                }
            }
        }
        if (tr[target] < 0) cout << -1 << endl;
        else {
            cout << it[d[target]].h.x[0] << endl;
            vector<int> res;
            int u = target;
            res.push_back(u);
            while (u != start) {
                int v = tr[u];
                res.push_back(v);
                u = v;
            }
            cout << res.size() << endl;
            FORD(i,SZ(res)-1,0) cout << res[i] << ' '; cout << endl;
        }
    }
    return 0;
}
