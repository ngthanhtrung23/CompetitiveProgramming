
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

typedef unsigned int uint;

// NOTE: gP(n) is incorrect for even values of n
#define N 310000000
uint mark[N / 64];
#define gP(n) (mark[n>>6]&(1<<((n>>1)&31)))
#define rP(n) (mark[n>>6]&=~(1<<((n>>1)&31)))

void sieve() {
    memset( mark, -1, sizeof( mark ) );
    uint i;
    uint sqrtN = ( uint )sqrt( ( double )N ) + 1;

    for( i = 3; i < sqrtN; i += 2 ) if( gP( i ) ) {
        uint i2 = i + i;
        for( uint j = i * i; j < N; j += i2 ) rP( j );
    }
}

int main() {
    int l, r;
    while (cin >> l >> r) {
        sieve();
        int res = 0;
        if (l == 1) ++l;
        FOR(i,l,r) if (i == 2 || (gP(i) && i % 4 == 1)) {
            ++res;
        }
        cout << res << endl;
    }
    return 0;
}

