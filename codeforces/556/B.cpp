
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

int a[1011];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        REP(i,n) cin >> a[i];
        int x = n - a[0];

        bool can = true;
        FOR(i,1,n-1) {
            int cur = a[i];
            if (i % 2 == 1) cur = (cur - x + n) % n;
            else cur = (cur + x) % n;

            if (cur != i) can = false;
        }
        cout << (can ? "Yes" : "No") << endl;
    }
}
