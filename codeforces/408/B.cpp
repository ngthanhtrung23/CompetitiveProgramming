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

string a, b;
int cnta[311], cntb[311];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> a >> b) {
        memset(cnta, 0, sizeof cnta);
        memset(cntb, 0, sizeof cntb);

        for(char c : a) ++cnta[c];
        for(char c : b) ++cntb[c];

        int res = 0;
        FOR(c,'a','z') {
            if (min(cnta[c], cntb[c]) == 0 && cntb[c]) {
                res = -1;
                break;
            }
            res += min(cnta[c], cntb[c]);
        }
        cout << res << endl;
    }
    return 0;
}

