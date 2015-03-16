
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

int n, res[211];
char a[111];

bool bad() {
    FOR(i,1,n/2) if (abs(res[i] - res[i+n/2]) == 1) return true;
    return false;
}

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    while (cin >> n >> a) {
        int t = 0;
        REP(i,n) if (a[i] == 'L') res[++t] = i;
        FORD(i,n-1,0) if (a[i] == 'R') res[++t] = i;

        while (bad()) {
            random_shuffle(res+1, res+n/2+1);
        }

        FOR(i,1,n/2) cout << res[i] + 1 << ' ' << res[i + n/2] + 1 << endl;
    }
    return 0;
}
