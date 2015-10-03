
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

const int MN = 1011;
int n, a[MN], done[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) done[i] = 0;

        int has = 0, turn = -1;
        while (has < n) {
            ++turn;
            if (turn % 2 == 0) {
                FOR(i,1,n) if (!done[i])
                    if (has >= a[i]) {
                        ++has;
                        done[i] = 1;
                    }
            }
            else {
                FORD(i,n,1) if (!done[i])
                    if (has >= a[i]) {
                        ++has;
                        done[i] = 1;
                    }
            }
        }
        cout << turn << endl;
    }
}
