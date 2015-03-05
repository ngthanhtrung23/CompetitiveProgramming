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

struct Hash {
    ll x, y;
    Hash(ll x = 0, ll y = 0) : x(x), y(y) {}

    Hash operator + (const Hash& a) const { return Hash((x+a.x) % MOD, y+a.y); }
    Hash operator - (const Hash& a) const { return Hash((x-a.x+MOD) % MOD, y-a.y); }
    Hash operator * (const ll& k) const { return Hash(x*k%MOD, y*k); }
    Hash operator * (const Hash& a) const { return Hash(x*a.x%MOD, y*a.y); }
} p[2011], hs[2011], ha, hb, hai[2011], hbj[2011];

bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}
bool operator < (const Hash& a, const Hash& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
char a[2011], b[2011], s[2011];

Hash getHash(int from, int to) {
    if (from == 0) return hs[to];
    else return hs[to] - hs[from - 1];
}

int main() {
    p[0] = Hash(1, 1);
    FOR(i,1,2000) p[i] = p[i-1] * 31;

    while (gets(s) && gets(a) && gets(b)) {
        ha = Hash(0, 0);
        hb = Hash(0, 0);
        int la = strlen(a);
        int lb = strlen(b);
        REP(i,la) ha = ha + p[i] * (a[i] - 'a' + 1);
        REP(i,lb) hb = hb + p[i] * (b[i] - 'a' + 1);

        int ls = strlen(s);
        Hash tmp = Hash(0, 0);
        REP(i,ls) {
            tmp = tmp + p[i] * (s[i] - 'a' + 1);
            hs[i] = tmp;
        }
        int cnt = 0;
        REP(i,ls) hai[i] = ha * p[i];
        REP(j,ls) hbj[j] = hb * p[j-lb+1];

        int res = 0;
        FOR(len,0,ls-1) {
            set<Hash> all;
            REP(i,ls-len) {
                int j = i + len;
                int len = j - i + 1;
                if (len >= la && len >= lb) {
                    // i --> i + la - 1
                    // j - lb + 1 --> j

                    if (getHash(i, i+la-1) == hai[i]
                            && getHash(j-lb+1, j) == hbj[j]) {
                        all.insert(getHash(i, j) * p[2000-i]);
                    }
                }
            }
            res += all.size();
        }
        cout << res << endl;
    }
    return 0;
}

