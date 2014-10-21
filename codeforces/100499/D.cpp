#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

// NOTE: gP(n) is incorrect for even values of n
#define N 1000000
unsigned int mark[N / 64];
#define gP(n) (mark[n>>6]&(1<<((n>>1)&31)))
#define rP(n) (mark[n>>6]&=~(1<<((n>>1)&31)))

int cnt[N + 1];

void sieve() {
    memset( mark, -1, sizeof( mark ) );
    unsigned int i;
    unsigned int sqrtN = ( unsigned int )sqrt( ( double )N ) + 1;

    for( i = 3; i < sqrtN; i += 2 ) if( gP( i ) ) {
        unsigned int i2 = i + i;
        for( unsigned int j = i * i; j < N; j += i2 ) rP( j );
    }
    cnt[1] = 1;
    cnt[2] = 1;
    for( i = 3; i < N; i += 2)
        if (gP(i)) cnt[i] = 1;

    for(int i=1; i <= N; ++i) cnt[i] += cnt[i-1];
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    sieve();
    int ntest; cin >> ntest;
    for(int test = 1; test <= ntest; ++test) {
        int n; cin >> n;
        cout << "Case #" << test << ": " << cnt[n] << endl;
    }
    return 0;
}
