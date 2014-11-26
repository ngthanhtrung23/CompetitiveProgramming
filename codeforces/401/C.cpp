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

const int MN = 1000111;
int a[MN], one, zero;
int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> zero >> one) {
        if (one < zero - 1) cout << -1 << endl;
        else if (one > (zero + 1) * 2) cout << -1 << endl;
        else {
            memset(a, 0, sizeof a);
            FOR(i,1,zero-1) {
                if (one) ++a[i], --one;
            }

            FOR(i,0,zero) {
                if (one && a[i] < 2) ++a[i], --one;
                if (one && a[i] < 2) ++a[i], --one;
            }

            while (a[0]--) cout << 1;
            FOR(i,1,zero) {
                cout << 0;
                while (a[i]--) cout << 1;
            }
            cout << endl;
        }
    }
    return 0;
}
