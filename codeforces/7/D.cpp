
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 5000111;

char tmp[MN];

string s, t;
long long hs[MN], ht[MN], p[MN];
int f[MN];

int main() {
    p[0] = 1;
    FOR(i,1,MN-1) p[i] = p[i-1] * 311LL;

    while (gets(tmp)) {
        s = string(tmp); t = s;
        int n = s.length();
        reverse(t.begin(), t.end());

        s = " " + s;
        t = " " + t;

        FOR(i,1,n) {
            hs[i] = hs[i-1] + s[i] * p[i];
            ht[i] = ht[i-1] + t[i] * p[i];
        }
        long long sum = 0;
        FOR(i,1,n) {
            int from = n - i + 1;
            if (hs[i] * p[from-1] == ht[n] - ht[from-1]) {
                f[i] = f[i/2] + 1;
            }
            else f[i] = 0;
            sum += f[i];
        }
        cout << sum << endl;
    }
}
