
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

int a[511][511];
int sieve[1000111], primes[1000111];

void init() {
    FOR(i,2,1000) if (sieve[i] == 0) {
        for(int j=i*i; j <= 1000*1000; j += i) {
            sieve[j] = i;
        }
    }
    sieve[1] = 1;

    FORD(i,1000*1000,1)
        if (sieve[i] == 0) primes[i] = i;
        else primes[i] = primes[i+1];
}

int main() {
    ios :: sync_with_stdio(false);
    init();
    int m, n;
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) {
            int x; cin >> x;
            a[i][j] = primes[x] - x;
        }
        int best = 1000111000;
        FOR(i,1,m) {
            int cur = 0;
            FOR(j,1,n) cur += a[i][j];
            best = min(best, cur);
        }
        FOR(j,1,n) {
            int cur = 0;
            FOR(i,1,m) cur += a[i][j];
            best = min(best, cur);
        }
        cout << best << endl;
    }
    return 0;
}
