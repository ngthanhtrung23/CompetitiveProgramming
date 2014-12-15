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

string s;
int n;
int cnt[33][100111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cout << "Case #" << test << ":\n";
        cin >> s; n = s.length(); s = " " + s;

        REP(c,26) {
            FOR(i,1,n) {
                cnt[c][i] = cnt[c][i-1];
                if (s[i] == c + 'A') ++cnt[c][i];
            }
        }

        int q; cin >> q;
        while (q--) {
            char typ; int l, r; cin >> typ >> l >> r;
            ++l; ++r;
            if (typ == 'g') {
                REP(c,26) cout << cnt[c][r] - cnt[c][l-1] << ' ';
                cout << "\n";
            }
            else {
                sort(s.begin()+l, s.begin()+r+1);
                REP(c,26) {
                    FOR(i,l,r) {
                        cnt[c][i] = cnt[c][i-1];
                        if (s[i] == c + 'A') ++cnt[c][i];
                    }
                }
            }
        }
    }
    return 0;
}
