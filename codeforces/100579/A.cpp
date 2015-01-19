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

const int MN = 10111000;
int sieve[MN], f[MN];

void init() {
    FOR(i,2,4000) if (!sieve[i]) {
        int j = i*i;
        while (j < MN) {
            sieve[j] = i;
            j += i;
        }
    }
    f[1] = 0;
    FOR(i,2,MN-1) {
        if (!sieve[i]) f[i] = 1;
        else {
            int u = i;
            while (u % sieve[i] == 0) u /= sieve[i];
            f[i] = f[u] + 1;
        }
    }
//    PR(f, 10);
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    init();
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int a, b, k; cin >> a >> b >> k;
        int cnt = 0;
        FOR(i,a,b) if (f[i] == k) ++cnt;

        cout << "Case #" << test << ": " << cnt << endl;
    }
    return 0;
}
