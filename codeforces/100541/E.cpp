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

const int MN = 50111;

struct Node {
    long long sum, cover;
} it[40][MN * 4];

vector< pair<int,int> > factors[155];
int nPrime, primes[155], n, q;

bool isPrime(int n) {
    for(int i = 2; i*i <= n; ++i)
        if (n % i == 0) return false;
    return n > 1;
}

void init() {
    FOR(i,1,155) if (isPrime(i)) {
        primes[++nPrime] = i;
    }
    FOR(i,1,155) {
        int u = i;
        FOR(p,1,nPrime) if (u % primes[p] == 0) {
            int cnt = 0;
            while (u % primes[p] == 0) {
                ++cnt;
                u /= primes[p];
            }
            factors[i].push_back(make_pair(p, cnt));
        }
    }
}

long long power(long long x, long long k, long long MOD) {
    if (k == 0) return 1 % MOD;
    if (k == 1) return x % MOD;
    long long mid = power(x * x % MOD, k >> 1, MOD);
    if (k & 1) return mid * x % MOD;
    else return mid;
}

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

void down(int p, int i, int l, int r, int mid) {
    if (it[p][i].cover) {
        long long t = it[p][i].cover;
        it[p][CT(i)].cover += t;
        it[p][CT(i)].sum += t * (mid - l + 1LL);

        it[p][CP(i)].cover += t;
        it[p][CP(i)].sum += t * (r - mid);

        it[p][i].cover = 0;
    }
}

void up(int p, int i) {
    it[p][i].sum = it[p][CT(i)].sum + it[p][CP(i)].sum;
}

long long get(int p, int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[p][i].sum;

    int mid = (l + r) >> 1;
    down(p, i, l, r, mid);
    long long res = get(p, CT(i), l, mid, u, v) + get(p, CP(i), mid+1, r, u, v);
    up(p, i);
    return res;
}

void update(int p, int i, int l, int r, int u, int v, long long val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[p][i].cover += val;
        it[p][i].sum += val * (r - l + 1LL);
        return ;
    }
    int mid = (l + r) >> 1;
    down(p, i, l, r, mid);
    update(p, CT(i), l, mid, u, v, val);
    update(p, CP(i), mid+1, r, u, v, val);
    up(p, i);
}

long long get(int p, int u, int v) {
    if (u <= v) return get(p, 1, 1, n, u, v);
    else return get(p, 1, 1, n, u, n) + get(p, 1, 1, n, 1, v);
}

void update(int p, int u, int v, int val) {
    if (u <= v) update(p, 1, 1, n, u, v, val);
    else {
        update(p, 1, 1, n, u, n, val);
        update(p, 1, 1, n, 1, v, val);
    }
}

int main() {
    init();
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        scanf("%d%d", &n, &q);
        memset(it, 0, sizeof it);
        while (q--) {
            int typ, u, v, val; scanf("%d%d%d%d", &typ, &u, &v, &val);
            if (typ == 0) {
                long long res = 1;
                FOR(p,1,nPrime) {
                    long long k = get(p, u, v);
                    res = res * power(primes[p], k, val) % val;
                }
                printf("%d\n", (int) (res % val));
            }
            else if (typ == 1) {
                for(auto x : factors[val]) {
                    update(x.first, u, v, x.second);
                }
            }
            else if (typ == 2) {
                for(auto x : factors[val]) {
                    update(x.first, u, v, -x.second);
                }
            }
        }
    }
    return 0;
}
