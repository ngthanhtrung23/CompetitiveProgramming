
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

int c[30][30];
char a[11];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n && n) {
        memset(c, 0, sizeof c);
        FOR(turn,1,n) {
            string s; cin >> s;
            FOR(i,0,s.length()-1) FOR(j,i+1,s.length()-1)
                c[s[j] - 'A'][s[i] - 'A'] += 1;
        }

        string res = "";
        int best = 1000111000;
        REP(i,5) a[i] = i;
        do {
            int cur = 0;
            REP(i,5) FOR(j,i+1,4)
                cur += c[a[i]][a[j]];

            if (cur < best) {
                best = cur;
                res = "";
                REP(i,5) res += (char) ('A' + a[i]);
            }
        } while (next_permutation(a, a+5));

        cout << res << " is the median ranking with value " << best << ".\n";
    }
    return 0;
}
