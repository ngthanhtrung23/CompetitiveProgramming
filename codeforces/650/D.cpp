#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 800111;

int n, q, a[MN], c[MN], nc;
pair<int,int> queries[MN];
int res[MN];
vector<int> ls[MN];

const int MOD = 1e9 + 7;
struct Hash {
    int x, y;
    Hash() { x = y = 0; }
    Hash(int x, int y) : x(x), y(y) {}

    Hash operator + (const Hash& a) const { return Hash((x+a.x) % MOD, y+a.y); }
    Hash operator * (const Hash& a) const { return Hash((x*a.x) % MOD, y*a.y); }
};
ostream& operator << (ostream& cout, const Hash& h) {
    cout << h.x << ' ' << h.y;
    return cout;
}
bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}
pair<int,Hash> f1[MN], f2[MN], bit[MN];

void update(int u, int val, Hash h) {
    for(; u < MN; u += u & -u) {
        if (bit[u].first < val) {
            bit[u].first = val;
            bit[u].second = h;
        }
        else if (bit[u].first == val) {
            bit[u].second = bit[u].second + h;
        }
    }
}
pair<int,Hash> get(int u) {
    pair<int,Hash> res;
    res.first = 0;
    res.second = Hash(1, 1);

    for(; u > 0; u -= u & -u) {
        if (res.first < bit[u].first) {
            res.first = bit[u].first;
            res.second = bit[u].second;
        }
        else if (res.first == bit[u].first) {
            res.second = res.second + bit[u].second;
        }
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%lld%lld", &n, &q) == 2) {
        nc = 0;
        FOR(i,1,n) {
            scanf("%lld", &a[i]);
            c[++nc] = a[i];
            ls[i].clear();
        }
        FOR(i,1,q) {
            scanf("%lld%lld", &queries[i].first, &queries[i].second);
            c[++nc] = queries[i].second;
        }
        sort(c+1, c+nc+1);
        nc = unique(c+1, c+nc+1) - c - 1;
        FOR(i,1,n) a[i] = lower_bound(c+1, c+nc+1, a[i]) - c;
        FOR(i,1,q) queries[i].second = lower_bound(c+1, c+nc+1, queries[i].second) - c;

        FOR(i,1,q) ls[queries[i].first].push_back(i);

        memset(bit, 0, sizeof bit);
        memset(res, 0, sizeof res);

        // xuoi
        FOR(i,1,n) {
            f1[i] = get(a[i] - 1);
            f1[i].first++;

            for(int qid : ls[i]) {
                auto cur = get(queries[qid].second - 1);
                res[qid] = cur.first + 1;
            }
            update(a[i], f1[i].first, f1[i].second);
        }
        // nguoc
        memset(bit, 0, sizeof bit);
        FORD(i,n,1) {
            int val = nc - a[i] + 1;
            f2[i] = get(val - 1);
            f2[i].first++;

            for(int qid : ls[i]) {
                auto cur = get(nc - queries[qid].second);
                res[qid] += cur.first;
            }
            update(val, f2[i].first, f2[i].second);
        }
        int best = 0;
        Hash all(0, 0);
        FOR(i,1,n) {
            if (f1[i].first > best) {
                best = f1[i].first;
                all = f1[i].second;
            }
            else if (f1[i].first == best) {
                all = all + f1[i].second;
            }
        }

        FOR(i,1,q) {
            int u = queries[i].first;

            int cur = res[i]; // best result going through u

            // best result not going through u
            if (f1[u].first + f2[u].first == best + 1
                    && f1[u].second * f2[u].second == all) {
                cur = max(cur, best - 1);
            }
            else cur = max(cur, best);
            printf("%lld\n", cur);
        }
    }
}
