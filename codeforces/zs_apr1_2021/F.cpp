// p1: a+b
// p2: a = x^2 mod b
// p3: japanese

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
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

set<int> sq[100111];

string fix(string s, string rep) {
    return s.substr(0, SZ(s) - 2) + rep;
}

string solve3(string s) {
    if (SZ(s) > 50) {
        return "String is too long.";
    }
    if (s == "iku") {
        return "itte";
    }
    string t = "";
    switch (s[SZ(s) - 2]) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            t = "";
            t += s[SZ(s) - 2];
            t += "tte";
            return fix(s, t);

        case 'b':
            return fix(s, "nde");
        case 'g':
            return fix(s, "ide");
        case 'k':
            return fix(s, "ite");
        case 'm':
            return fix(s, "nde");
        case 'n':
            return fix(s, "nde");
        case 'r':
            return "ambiguous";
        case 's':
            if (SZ(s) >= 3 && s[SZ(s) - 3] == 't') {
                return s.substr(0, SZ(s) - 3) + "tte";
            }
            return fix(s, "shite");
        default:
            assert(false);
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest, typ; cin >> ntest >> typ;
    if (typ == 1) {
        while (ntest--) {
            int a, b; cin >> a >> b;
            cout << a + b << endl;
        }
    } else if (typ == 2) {
        while (ntest--) {
            int a, b; cin >> a >> b;
            if (sq[b].empty()) {
                REP(i,b) sq[b].insert(i*i % b);
            }
            a %= b;
            cout << (sq[b].count(a) ? "YES" : "NO") << endl;
        }
    } else if (typ == 3) {
        while (ntest--) {
            string s; cin >> s;
            assert(s.back() == 'u');
            assert(SZ(s) >= 2);

            cout << solve3(s) << endl;
        }
    } else if (typ == 4) {
        const string MES = "Sorry, the message is hidden by some outside disturbance. We are sorry for the inconvenience caused.";
        while (ntest--) {
            int n; cin >> n;
            cout << MES << endl;
        }
    } else if (typ == 5) {
        while (ntest--) {
            int n; cin >> n;
            assert(n == 1);
        }
    }
    return 0;
}

/*
 ***** p5

1 - 3
2 - 17
0 - 0
3 - 17
2 - 87
2 - 469
0 - 0
1 - 3
2 - 17
0 - 0

1 - 3
1 - 7
1 - 17
1 - 41
1 - 99
1 - 239
1 - 577
1 - 1393
1 - 3363
1 - 8119
1 - 19601
1 - 47321
1 - 114243
1 - 275807
1 - 665857
1 - 1607521
1 - 3880899
1 - 9369319
1 - 22619537
1 - 54608393
1 - 131836323
1 - 318281039
1 - 768398401
1 - 855077834
1 - 478554055

0 - 0
2 - 7
2 - 37
2 - 199
2 - 1069
2 - 5743
2 - 30853

 */
