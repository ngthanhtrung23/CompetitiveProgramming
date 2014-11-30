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

const int MN = 100111;
int na, nb;
unsigned long long a[MN], b[MN], suma[MN], sumb[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> na >> nb) {
        FOR(i,1,na) cin >> a[i];
        FOR(i,1,nb) cin >> b[i];
        sort(a+1, a+na+1, greater<long long>());
        sort(b+1, b+nb+1, greater<long long>());

        FOR(i,1,na) suma[i] = suma[i-1] + a[i];
        FOR(i,1,nb) sumb[i] = sumb[i-1] + b[i];

        // a[1, na] --> [1, k]
        unsigned long long res = 10001110001110001110LL;
        FOR(k,1,nb) {
            res = min(res, (suma[na] * k) - sumb[k] + sumb[nb]);
        }
        // b[1, nb] --> [1, k]
        FOR(k,1,na) {
            res = min(res, (sumb[nb] * k) - suma[k] + suma[na]);
        }
        cout << res << endl;
    }
    return 0;
}
