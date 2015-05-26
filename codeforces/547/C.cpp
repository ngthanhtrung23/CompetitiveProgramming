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

const int MN = 1000111;

int n, q, a[MN], cnt[MN];
int exist[MN], sieve[MN];

void init() {
    FOR(i,2,1000) if (!sieve[i]) {
        for(int j=i*i; j < MN; j += i)
            sieve[j] = i;
    }
}

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))
int main() {
    ios :: sync_with_stdio(false);
    init();

    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);

        memset(cnt, 0, sizeof cnt);
        memset(exist, 0, sizeof exist);

        long long res = 0;
        while (q--) {
            int x; scanf("%d", &x);
            int saveid = x;
            x = a[x];

            vector<int> primes;
            while (x > 1) {
                int p = (sieve[x] ? sieve[x] : x);
                while (x % p == 0) x /= p;

                primes.push_back(p);
            }
            
            REP(mask,TWO(primes.size())) {
                int prod = 1;
                REP(i,primes.size()) if (CONTAIN(mask, i)) prod *= primes[i];

                if (!exist[saveid]) {
                    if (__builtin_popcount(mask) & 1) res -= cnt[prod];
                    else res += cnt[prod];

                    cnt[prod]++;
                } else {
                    cnt[prod]--;

                    if (__builtin_popcount(mask) & 1) res += cnt[prod];
                    else res -= cnt[prod];
                }

//                cout << prod << ' ' << res << endl;
            }
            exist[saveid] = !exist[saveid];

            printf("%I64d\n", res);
        }
    }
    return 0;
}
