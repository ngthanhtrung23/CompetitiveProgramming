
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

char rev(char c) {
    if (c == 'E' || c == 'W') return 'E' + 'W' - c;
    return 'N' + 'S' - c;
}

const int MN = 1000111;
const ll MOD = 1e9 + 7;

struct Hash {
    ll x, y;
    Hash() {}
    Hash(ll x, ll y) : x(x), y(y) {}

    Hash operator + (const Hash& a) {
        return Hash(x+a.x, (y+a.y) % MOD);
    }
    Hash operator - (const Hash& a) {
        return Hash(x-a.x, (y-a.y+MOD) % MOD);
    }
    Hash operator * (ll k) {
        return Hash(x*k, y*k % MOD);
    }
    Hash operator * (const Hash& a) {
        return Hash(x*a.x, y*a.y % MOD);
    }
} p[MN], ha[MN], hb[MN];

bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    string a, b;
    int n;
    while (cin >> n >> a >> b) {
        --n;
        a = " " + a + " ";
        b = " " + b + " ";
        string revb = " ";
        FORD(i,n,1) {
            revb += rev(b[i]);
        }

        p[0] = Hash(1, 1);
        FOR(i,1,MN-1) p[i] = p[i-1] * 31;

        FOR(i,1,n) {
            ha[i] = ha[i-1] + p[i] * (a[i] - 'A' + 1);
            hb[i] = hb[i-1] + p[i] * (revb[i] - 'A' + 1);
        }

        bool ok = false;
        FOR(i,1,n) {
            int len = n - i + 1;

            auto h1 = ha[n] - ha[i-1];
            auto h2 = hb[len] * p[i-1];

            if (h1 == h2) {
                cout << "NO" << endl;
                ok = true;
                break;
            }
        }
        if (!ok) cout << "YES" << endl;
    }
}
