#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define int long long
using namespace std;

#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

using Seq = vector<int>;
Seq pattern;
vector<Seq> queries;

int nVal = 0;
map<int,int> valToIds;

Seq read(int l) {
    Seq res(l);
    for (int& val : res) cin >> val;
    return res;
}

int f_pattern[300111], f_query[300111];

void update(int f[], int u, int val) {
    for (; u < 300111; u += u & (-u)) {
        f[u] += val;
    }
}

int get(int f[], int u) {
    int res = 0;
    for (; u > 0; u -= u & (-u)) {
        res += f[u];
    }
    return res;
}

int inv_pattern;
int countInversions(const vector<int>& a) {
    int res = 0;

    REP(i,SZ(a)) {
        res += i - get(f_query, a[i]);
        update(f_query, a[i], +1);
    }

    for (int val : a) {
        update(f_query, val, -1);
    }

    return res;
}

int solve(const vector<int>& pat, const vector<int>& query) {
    int cur = inv_pattern;
    
    // Count inversions of combined seq
    REP(i, SZ(query)) {
        cur += SZ(pat) - get(f_pattern, query[i]);
        cur += i - get(f_query, query[i]);

        update(f_query, query[i], +1);
    }

    // Remove query
    for (int val : query) {
        update(f_query, val, -1);
    }

    // DEBUG(cur);
    int res = cur;

    REP(i,SZ(query)) {
        int x = query[i];
        int smaller = get(f_pattern, x - 1);
        int larger = SZ(pat) - get(f_pattern, x);

        cur += smaller;
        cur -= larger;

        res = min(res, cur);
    }

    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int lPattern, nQuery;
    cin >> lPattern >> nQuery;
    pattern = read(lPattern);

    queries.resize(nQuery);
    REP(i,nQuery) {
        int l; cin >> l;
        queries[i] = read(l);
    }

    // RR
    for (auto val : pattern) valToIds[val] = 0;
    for (auto q : queries) {
        for (auto val : q) valToIds[val] = 0;
    }

    nVal = 0;
    for (auto it = valToIds.begin(); it != valToIds.end(); it++) {
        it->second = ++nVal;
    }

    REP(i,lPattern) {
        pattern[i] = valToIds[pattern[i]];
    }
    for (auto& query : queries) {
        REP(i,SZ(query)) {
            query[i] = valToIds[query[i]];
        }
    }

    /*
    PR0(pattern, SZ(pattern));
    for (auto q : queries) {
        PR0(q, SZ(q));
    }
    */

    for (auto val : pattern) {
        update(f_pattern, val, +1);
    }
    inv_pattern = countInversions(pattern);

    // PR0(pattern, SZ(pattern));
    for (auto q : queries) {
        cout << solve(pattern, q) << '\n';
    }
    return 0;
}

