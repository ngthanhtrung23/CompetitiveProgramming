
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

const ll MOD = 1e9 + 7;
const int MN = 1000111;

struct Hash {
    ll x, y;
    Hash(ll x = 0, ll y = 0) : x(x), y(y) {}

    Hash operator + (const Hash& a) const { return Hash((x+a.x) % MOD, y+a.y); }
    Hash operator - (const Hash& a) const { return Hash((x-a.x+MOD) % MOD, y-a.y); }
    Hash operator * (const Hash& a) const { return Hash((x*a.x) % MOD, y*a.y); }
    Hash operator * (ll k) { return Hash((x*k) % MOD, y*k); }
} h[MN], power[MN];

bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}

int n, k;
string p;
int mark[MN];

void init() {
    power[0] = Hash(1, 1);
    FOR(i,1,MN - 1) power[i] = power[i-1] * 31;
}

bool equal(int i, int j, int u, int v) {
    Hash h1 = h[j] - h[i-1];
    Hash h2 = h[v] - h[u-1];
    return h1 * power[u] == h2 * power[i];
}

int main() {
    init();
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        memset(mark, 0, sizeof mark);
        cin >> p;
        int lp = p.length();
        p = " " + p;
        FOR(i,1,lp) {
            h[i] = h[i-1] + power[i] * (p[i] - 'a' + 1);
        }

        int u, v, x, y;
        bool can = true;
        FOR(i,1,k) {
            cin >> x;
            int y = x + lp - 1;

            mark[x]++;
            mark[y+1]--;

            if (i > 1) {
                if (x <= v) {
                    int l = v - x + 1;
                    can = can && equal(1, l, lp - l + 1, lp);
                }
            }

            u = x;
            v = y;
        }
        if (!can) {
            cout << 0 << endl;
            continue;
        }
        long long res = 1;
        FOR(i,1,n) {
            mark[i] += mark[i-1];
            if (mark[i] == 0) res = (res * 26LL) % MOD;
        }
        cout << res << endl;
    }
    return 0;
}

