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

int n;
int a[1011], b[1011];

int main() {
    while (cin >> n) {
        // suma * maxb
        FOR(i,1,n) cin >> a[i] >> b[i];

        int res = 2000111000;
        FOR(maxb,1,1000) {
            bool can = true;
            FOR(i,1,n) if (a[i] > maxb && b[i] > maxb) {
                can = false;
                break;
            }
            if (!can) continue;


            int suma = 0, lie = 0;
            vector<int> change;
            FOR(i,1,n) {
                if (a[i] > maxb) {
                    // can only stand
                    suma += a[i];
                }
                else if (b[i] > maxb) {
                    // can only lie
                    suma += b[i];
                    lie++;
                }
                else {
                    suma += a[i];
                    change.push_back(b[i] - a[i]);
                }
            }

            res = min(res, maxb * suma);
            sort(change.begin(), change.end());

            REP(i,change.size()) {
                ++lie;
                suma += change[i];
                res = min(res, suma * maxb);
            }
        }
        cout << res << endl;
    }
    return 0;
}