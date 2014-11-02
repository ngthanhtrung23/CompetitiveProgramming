#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int n, a[111];
int f[111][TWO(16)], trace[111][TWO(16)];

int primes[66], nPrime;
int factor_mask[66];

bool isPrime(int n) {
    for(int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return false;
    return n > 1;
}

void init() {
    FOR(i,1,58)
        if (isPrime(i)) {
            primes[nPrime] = i;
            ++nPrime;
        }
    // PR0(primes, nPrime);
    // DEBUG(nPrime);

    FOR(i,1,58) {
        REP(p,nPrime)
            if (i % primes[p] == 0)
                factor_mask[i] |= TWO(p);
        // if (i <= 10) {
            // DEBUG(i);
            // DEBUG(factor_mask[i]);
        // }
    }
}

void print(int n, int mask) {
    if (n == 0) return ;
    int b = trace[n][mask];

    print(n-1, mask - factor_mask[b]);
    cout << b << ' ';
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    init();
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        memset(f, -1, sizeof f);
        f[0][0] = 0;
        // f(i, S) + b(i+1) --> f(i+1, S')
        FOR(i,0,n-1) {
            FOR(b,1,58) {
                int S = TWO(nPrime) - 1 - factor_mask[b];
                for(int s = S; s >= 0; s = (s - 1) & S) {
                    if (f[i][s] >= 0) {
                        int new_s = s + factor_mask[b];

                        if (f[i+1][new_s] < 0 || f[i+1][new_s] > f[i][s] + abs(b - a[i+1])) {
                            f[i+1][new_s] = f[i][s] + abs(b - a[i+1]);
                            trace[i+1][new_s] = b;
                        }
                    }
                    if (s == 0) break;
                }
            }
        }
        int best_s = 0;
        REP(s,TWO(nPrime))
            if (f[n][s] >= 0)
            if (f[n][best_s] < 0 || f[n][s] < f[n][best_s]) {
                best_s = s;
            }
        // DEBUG(f[n][best_s]);
        print(n, best_s);
        cout << endl;
    }
    return 0;
}

