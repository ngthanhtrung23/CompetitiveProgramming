
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 5011;
ll h[MN], p[MN];

ll getHash(int u, int v) {
    return (h[v] - h[u-1]) * p[5000 - u];
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("palindromes.in", "r", stdin);
    freopen("palindromes.out", "w", stdout);
    string s;
    p[0] = 1; FOR(i,1,MN-1) p[i] = p[i-1] * 31;

    while (cin >> s) {
        int n = SZ(s);
        s = " " + s + "-";
        unordered_set<ll> all;
        FOR(i,1,n) {
            h[i] = h[i-1] + (s[i] - 'A' + 1) * p[i];
        }

        // odd length
        FOR(i,1,n) {
            for(int l = i, r = i; s[l] == s[r]; --l, ++r)
                all.insert(getHash(l, r));
        }
        // even length
        FOR(i,1,n-1) {
            for(int l = i, r = i+1; s[l] == s[r]; --l, ++r)
                all.insert(getHash(l, r));
        }
        cout << SZ(all) << endl;
    }
}
