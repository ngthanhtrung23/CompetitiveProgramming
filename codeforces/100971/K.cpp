
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

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MOD = 1e9 + 7;
struct Hash {
    ll x, y;
    Hash(ll x = 0, ll y = 0) : x(x), y(y) {}

    Hash operator + (const Hash& a) const { return Hash((x+a.x) % MOD, y+a.y); }
    Hash operator - (const Hash& a) const { return Hash((x-a.x+MOD) % MOD, y-a.y); }
    Hash operator * (const Hash& a) const { return Hash((x*a.x) % MOD, y*a.y); }
    Hash operator * (ll k) { return Hash((x*k) % MOD, y*k); }

    friend ostream& operator << (ostream& cout, const Hash& h) {
        cout << h.x << ' ' << h.y;
        return cout;
    }
};
bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}
bool operator < (const Hash& a, const Hash& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

const int MN = 200111;
Hash h1[MN], h2[MN], p[MN];
int n;
string s, t;

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    p[0] = Hash(1, 1);
    FOR(i,1,MN-1) p[i] = p[i-1] * 311;

    while (cin >> s) {
        n = SZ(s);
        t = s;
        reverse(t.begin(), t.end());

        s = " " + s + " ";
        t = " " + t + " ";

        FOR(i,1,n) {
            h1[i] = h1[i-1] + p[i] * s[i];
            h2[i] = h2[i-1] + p[i] * t[i];
        }

        int res = -1;
        FOR(i,1,n) {
            Hash xuoi = (h1[n] - h1[i]) + (h1[i-1] * p[1]);
            Hash nguoc = (h2[n] - h2[n-i+1]) + (h2[n-i] * p[1]);

            if (xuoi == nguoc) {
                res = i;
                break;
            }
        }
        if (res < 0) cout << "NO" << endl;
        else cout << "YES" << endl << res << endl;
    }
}
