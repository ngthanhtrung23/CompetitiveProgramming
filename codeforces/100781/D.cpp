
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

const int MN = 102111;
int a[MN], n, k;

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &k) == 2) {
        memset(a, 0, sizeof a);
        FOR(i,1,n) {
            int x; scanf("%d", &x);
            a[x]++;
            a[x+1000]--;
        }
        int res = 0;
        FOR(i,1,MN-1) {
            a[i] += a[i-1];
            res = max(res, a[i]);
        }
        int need = res / k;
        if (res % k) ++need;
        cout << need << endl;
    }
}

