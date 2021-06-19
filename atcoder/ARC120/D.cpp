// 4 3 2 1
//
// ( = +1
// ) = -1
// >= 0 every time
// == 0 at the end

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

const int MN = 400111;
int a[MN];
pair<int,int> b[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    int n; cin >> n;
    n *= 2;
    FOR(i,1,n) {
        cin >> a[i];
        b[i] = {a[i], i};
    }
    sort(b+1, b+n+1);
    FOR(i,1,n/2) a[b[i].second] = 0;
    FOR(i,n/2+1,n) a[b[i].second] = 1;

    int sum = 0;
    int open = -1;
    FOR(i,1,n) {
        if (sum == 0) {
            open = a[i];
            sum++;
            cout << '(';
            continue;
        }

        if (a[i] == open) {
            cout << '(';
            sum++;
            continue;
        }

        cout << ')';
        --sum;
    }
    cout << endl;
    return 0;
}
