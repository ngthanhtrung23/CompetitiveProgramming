#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
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

const string NO = "Bedao!";
const int MOD = 727355608;

void solveTest(int length) {
    vector<int> n(4);
    FOR(i,1,3) cin >> n[i];
    n[0] = length - n[1] - n[2] - n[3];

    string middle = "";
    if (length % 2 == 0) {
        for (int nx : n) {
            if (nx % 2) {
                cout << NO << endl;
                return;
            }
        }
    } else {
        REP(i,4) {
            if (n[i] % 2) {
                if (middle != "") {
                    cout << NO << endl;
                    return;
                }

                middle += (char) ('0' + i);
                n[i]--;
            }
        }
    }

    // first digit
    string left = "";
    REP(i,4) if (i > 0) {
        if (n[i]) {
            left += (char) ('0' + i);
            n[i] -= 2;
            break;
        }
    }
    if (left == "" && length > 1) {
        cout << NO << endl;
        return;
    }

    // for each digit 0 -> 3
    REP(i,4) {
        REP(_,n[i]/2) {
            left += (char) ('0' + i);
        }
    }

    string right = left;
    reverse(right.begin(), right.end());

    string s = left + middle + right;
    int res = 0;
    for (char c : s) {
        res = (res * 4 + (c - '0')) % MOD;
    }
    cout << res << endl;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int length;
    while (cin >> length) {
        solveTest(length);
    }
    return 0;
}
