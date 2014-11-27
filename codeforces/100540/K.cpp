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

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int a, b, c;
    while (cin >> a >> b >> c && a) {
        if (a == b && b == c) { // set
            if (a == 13) cout << '*' << endl;
            else {
                int x = a + 1;
                cout << x << ' ' << x << ' ' << x << endl;
            }
        }
        else if (a != b && b != c && c != a) {
            cout << 1 << ' ' << 1 << ' ' << 2 << endl;
        }
        else {
            int x, y;
            if (a == b) x = a, y = c;
            if (b == c) x = b, y = a;
            if (c == a) x = c, y = b;

            vector<int> res;
            bool ok = false;
            FOR(i,1,13) FOR(j,1,13) if (i != j) {
                if (ok) break;

                if (i > x || (i == x && j > y)) {
                    ok = true;
                    res = vector<int> {i, i, j};
                    break;
                }
            }
            if (!ok) res = vector<int> {1,1,1};
            sort(res.begin(), res.end());
            cout << res[0] << ' ' << res[1] << ' ' << res[2] << endl;
        }
    }
    return 0;
}
