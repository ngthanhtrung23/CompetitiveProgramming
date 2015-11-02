
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

const int MN = 1<<22;
int n;
int a[MN], val[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        memset(val, -1, sizeof val);
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            val[a[i]] = a[i];
        }
        REP(x,MN) {
            if (val[x] >= 0) continue;
            REP(bit,22) {
                if ((x >> bit) & 1) {
                    if (val[x - (1<<bit)] >= 0) {
                        val[x] = val[x - (1<<bit)];
                        break;
                    }
                }
            }
        }
        FOR(i,1,n) {
            int mask = MN - 1 - a[i];
            printf("%d ", val[mask]);
        }
        puts("");
    }
}
