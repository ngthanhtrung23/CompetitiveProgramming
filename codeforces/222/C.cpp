
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

const int MAX = 10111000;
const int MN = 100111;
int sieve[MAX], cnt[MAX], x[MN], y[MN], m, n;

void init() {
    for(int i = 2; i <= 4000; ++i) if (!sieve[i]) {
        for(int j = i*i; j < MAX; j += i) {
            sieve[j] = i;
        }
    }
}

void update(int u, int val) {
    while (sieve[u] || u > 1) {
        int p = sieve[u] ? sieve[u] : u;
        cnt[p] += val;
        u /= p;
    }
}

int get(int typ, int u) {
    int prod = 1;
    while (sieve[u] || u > 1) {
        int p = (sieve[u] ? sieve[u] : u);
        u /= p;

        if (typ == 1) {
            if (cnt[p] <= 0) {
                // ignore
            }
            else {
                cnt[p]--;
                prod *= p;
            }
        }
        else {
            if (cnt[p] >= 0) {
                // ignore
            }
            else {
                cnt[p]++;
                prod *= p;
            }
        }
    }
    return prod;
}

int main() {
    init();
    while (scanf("%d%d", &m, &n) == 2) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,m) {
            int a; scanf("%d", &a);
            update(a, +1);
            x[i] = a;
        }
        FOR(i,1,n) {
            int a; scanf("%d", &a);
            update(a, -1);
            y[i] = a;
        }

        printf("%d %d\n", m, n);
        FOR(i,1,m) {
            printf("%d ", get(1, x[i]));
        }
        puts("");
        FOR(i,1,n) {
            printf("%d ", get(2, y[i]));
        }
        puts("");
    }
    return 0;
}
