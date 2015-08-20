
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
using namespace std;

typedef unsigned int uint;

// NOTE: gP(n) is incorrect for even values of n
#define N 2000111
uint mark[N / 64 + 1];
#define gP(n) (mark[n>>6]&(1<<((n>>1)&31)))
#define rP(n) (mark[n>>6]&=~(1<<((n>>1)&31)))

// prime indexed from 0
uint prime[N], nprime;

void sieve() {
    memset( mark, -1, sizeof( mark ) );
    uint i;
    uint sqrtN = ( uint )sqrt( ( double )N ) + 1;

    for( i = 3; i < sqrtN; i += 2 ) if( gP( i ) ) {
        uint i2 = i + i;
        for( uint j = i * i; j < N; j += i2 ) rP( j );
    }
    nprime = 0;
    prime[nprime++] = 2;
    for( i = 3; i < N; i += 2)
        if (gP(i)) prime[nprime++] = i;
}

bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    return gP(n);
}

bool isPalin(int n) {
    if (n % 10 == 0) return false;
    int u = n, rev = 0;
    while (u) {
        rev = rev * 10 + u % 10;
        u /= 10;
    }
    return rev == n;
}

int main() {
    ios :: sync_with_stdio(false);
    sieve();
    ll p, q;
    while (cin >> p >> q) {
        int pi = 0, rub = 0;
        int res = 0;
        FOR(i,1,N) {
            if (isPrime(i)) ++pi;
            if (isPalin(i)) ++rub;

            if (pi * q <= p * rub) {
                res = i;
            }
        }
        cout << res << endl;
    }
}

