
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const long long MOD = 1e9 + 7;

struct Hash {
    ll x, y;

    Hash(ll x = 0, ll y = 0) : x(x), y(y) {}

    Hash operator + (const Hash &a) const { return Hash((x+a.x) % MOD, y+a.y); }
    Hash operator - (const Hash &a) const { return Hash((x-a.x+MOD) % MOD, y-a.y); }
    Hash operator * (const ll k) const { return Hash((x*k) % MOD, y*k); }
    Hash operator * (const Hash &a) const { return Hash((x*a.x) % MOD, y*a.y); }
};

bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}

const int MN = 1000111;
int n, k;
string s;
Hash h[MN], p[MN];
int res[MN];

vector<int> zfunc(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    ios :: sync_with_stdio(false);
    p[0] = Hash(1, 1);
    FOR(i,1,MN - 1) p[i] = p[i-1] * 31;

    while (cin >> n >> k) {
        cin >> s;
        REP(i,n) {
            if (i == 0) h[i] = Hash(s[i] - 'a' + 1, s[i] - 'a' + 1);
            else h[i] = h[i-1] + p[i] * (s[i] - 'a' + 1);
        }

//        DEBUG(s);
        vector<int> z = zfunc(s);
//        PR0(z, n);

        memset(res, 0, sizeof res);
        FOR(l,1,n/k) {
            Hash h0 = h[l-1];
            bool ok = true;
            for(int start = l, cnt = 2; cnt <= k; ++cnt, start += l) {
                Hash cur = h[start+l-1] - h[start-1];
                if (cur == h0 * p[start]) {
                }
                else ok = false;
            }
            if (ok) {
//                DEBUG(l);
                int start = k * l;
                int can = min(l, z[start]);
                res[start-1] += 1;
                res[start+can] -= 1;
            }
        }
        FOR(i,1,n) res[i] = res[i-1] + res[i];
        REP(i,n) if (res[i]) cout << '1'; else cout << '0';
        cout << endl;
    }
    return 0;
}
