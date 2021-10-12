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

const int MN = 10111;
int match[MN];
string s;

int solve(int l, int r) {
    // ()
    if (l == r - 1) return 0;

    // (T)
    if (l == match[r]) return solve(l + 1, r - 1);

    // T1 -> T2

    int sum = 0;
    FOR(i,l,r) {
        if (s[i] == ')') ++sum;
        else if (s[i] == '(') --sum;
        else if (s[i] == '>' && sum == 0) {
            int res = max(solve(l, i-2) + 1, solve(i+1, r));
            return res;
        }
    }
    assert(false);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> s;
    int n = SZ(s);
    s = " " + s + " ";

    stack<int> st;
    FOR(i,1,n) {
        char c = s[i];
        if (c == '(') st.push(i);
        else if (c == ')') {
            int j = st.top(); st.pop();
            match[i] = j;
            match[j] = i;
        }
    }
    cout << solve(1, n) << endl;
    return 0;
}
