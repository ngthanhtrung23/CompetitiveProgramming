
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

const int MAX = 11000111;
int n, a[1000111], sieve[MAX];
ll need[MAX];
int primes[MAX], nPrime;

void init() {
    FOR(i,2,4000) if (!sieve[i]) {
        for(int j = i*i; j < MAX; j += i)
            sieve[j] = i;
    }
    nPrime = 0;
    FOR(i,2,MAX-1) if (!sieve[i]) primes[++nPrime] = i;
//    PR(primes, 26);
}

ll get(int p, ll n) {
    if (n < p) return 0;
    return n/p + get(p, n/p);
}

bool check(ll x) {
    FOR(i,1,nPrime)
        if (get(primes[i], x) < need[primes[i]])
            return false;
    return true;
}

int has[MAX];

int main() {
    init();
    while (scanf("%d", &n) == 1) {
        memset(has, 0, sizeof has);
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            has[a[i]] += 1;
        }
        FORD(i,MAX-2,1) has[i] += has[i+1];

        memset(need, 0, sizeof need);
        int ln = *max_element(a+1, a+n+1);
        FOR(i,2,ln) {
            int u = i;
            while (u > 1) {
                int p = sieve[u] ? sieve[u] : u;

                while (u % p == 0) {
                    u /= p;
                    need[p] += has[i];
                }
            }
        }

        ll l = 1, r = 1e14, res = r;
        while (l <= r) {
            ll mid = (l + r) >> 1LL;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        cout << res << endl;
    }
    return 0;
}

