
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

int n, a[1011], k;

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    while (cin >> n >> k && n) {
        FOR(i,1,n) {
            string s; cin >> s;
            a[i] = s.length();
        }
        sort(a+1, a+n+1);

        bool can = true;
        for(int from = 1; from <= n; from += k) {
            int to = from + k;
            int sum = accumulate(a+from, a+to, 0);
            int nn = *min_element(a+from, a+to);
            int ln = *max_element(a+from, a+to);

            can = can && sum <= (2 + nn) * k;
            can = can && sum >= (-2 + ln) * k;
        }
        cout << "Case " << ++test << ": " << (can ? "yes" : "no") << endl;
    }
}
