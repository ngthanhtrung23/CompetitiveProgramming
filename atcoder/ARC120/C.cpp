// a(i) a(i+1)
// a(i+1)+1  a(i)-1
//
// a(i) + i
//
// A =        8 5 4 7 4 5
// A(i) + i = 8 6 6 10 8 10
// B(i) + i = 10 6 8 10 8 6
//
// B =        10 5 6 7 4 1

#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int MN = 200111;
int a[MN], b[MN], bit[MN];
int n;
map<int, vector<int>> ids;

void update(int u) {
    for (int x = u; x <= n; x += x & -x) {
        bit[x]++;
    }
}

int get(int u) {
    int res = 0;
    for (int x = u; x > 0; x -= x & -x) {
        res += bit[x];
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    while (cin >> n) {
        ids.clear();
        memset(bit, 0, sizeof bit);

        FOR(i,1,n) {
            cin >> a[i];
            a[i] += i;

            ids[a[i]].push_back(i);
        }
        FOR(i,1,n) {
            cin >> b[i];
            b[i] += i;
        }

        try {
            int res = 0;
            FORD(i,n,1) {
                if (ids[b[i]].empty()) {
                    throw 1;
                }

                int x = ids[b[i]].back();
                ids[b[i]].pop_back();

                res += get(x-1);
                update(x);
            }
            cout << res << endl;
        } catch (...) {
            cout << -1 << endl;
        }
    }
    return 0;
}
