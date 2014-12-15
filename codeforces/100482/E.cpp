#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

long long f[10111][1020];
pair<char,int> tr[10111][1020];
string s;

void trace(int n, int c) {
    if (n == 0) return ;
    trace(n-1, tr[n][c].second);
    cout << tr[n][c].first;
}

const int MOD = 1013;

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int c; cin >> c;
        cin >> s;
        memset(f, 0, sizeof f);
        f[0][0] = 1;

        int n = s.length();
        FOR(i,0,n-1) FOR(cur,0,MOD-1)
            if (f[i][cur]) {
                if (s[i] == '?') {
                    FOR(c,'a','z') {
                        f[i+1][(cur*31 + c) % MOD] += f[i][cur];
                        tr[i+1][(cur*31 + c) % MOD] = make_pair(c, cur);
                    }
                }
                else {
                    f[i+1][(cur*31 + s[i]) % MOD] += f[i][cur];
                    tr[i+1][(cur*31 + s[i]) % MOD] = make_pair(s[i], cur);
                }
            }

        cout << "Case #" << test << ": ";
        if (f[n][c] == 1) trace(n, c);
        else cout << f[n][c];
        cout << endl;
    }
    return 0;
}
