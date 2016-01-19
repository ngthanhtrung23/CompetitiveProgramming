
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 40111;
ll primes[MN], nPrime;
int sieve[MN];

void init() {
    FOR(i,2,1000) if (!sieve[i]) {
        int j = i*i;
        while (j < MN) {
            sieve[j] = i;
            j += i;
        }
    }
    FOR(i,2,MN-1) if (!sieve[i]) primes[++nPrime] = i;
//    DEBUG(nPrime);
//    PR(primes, 10);
}

ll f[33][33][33][33];

ll res[30] = {
1,
8,
30,
108,
338,
1042,
2997,
8405,
22651,
59520,
151957,
379692,
927621,
2224234,
5236585,
12130779,
27669592,
62229989,
138095695,
302673028,
655627974,
1404599866,
2977831388,
6251060784,
12999299704,
26791990051
};

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("false.in", "r", stdin);
    freopen("false.out", "w", stdout);
    init();
    ll n;
/*
    FOR(k,1,26) {
        memset(f, 0, sizeof f);
        f[0][0][0][0] = 1;
        FOR(u,0,k) FOR(v,0,k)
            FOR(lastu,0,u) FOR(lastv,0,v) {
                ll cur = f[u][v][lastu][lastv];
                if (!cur) continue;

                FOR(nextu,0,k-u)
                    FOR(nextv,0,k-v)
                    if (make_pair(nextu, nextv) >= make_pair(lastu, lastv)) {
                        f[u + nextu][v + nextv][nextu][nextv] += cur;
                    }
            }
        
        ll res = 0;
        FOR(u,0,k) FOR(v,0,k)
            res += f[k][k][u][v];
        cout << res - 1 << endl;
    }
    */
    while (cin >> n) {
        // find k
        int k = 1;
        FOR(i,1,nPrime) {
            int p = primes[i];
            if (n % p == 0) {
                int cur = 0;
                while (n % p == 0) {
                    ++cur;
                    n /= p;
                }
                k = cur;
                break;
            }
        }
//        DEBUG(k);

        // # non-trivial factorization
        cout << res[k-1] << endl;
    }
}
