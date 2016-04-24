
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
#define double long double
using namespace std;

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 100111;
const int NPRIME = 24;
const int MOD = 1e9 + 9;
int primes[NPRIME] = {
    3,5,7,11,13,
    17,19,23,29,31,
    37,41,43,47,53,
    59,61,67,71,73,
    79,83,89,97
};

int power(int x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    int mid = power(x, k >> 1);
    mid = mid * mid % MOD;
    if (k & 1) return mid * x % MOD;
    return mid;
}

typedef pair<double,int> P;
int a[NPRIME + 2];
int divs[100111], nDiv;
P res;

void attempt(int i, int prod, double sumlog, int cur) {
    if (i == NPRIME) {
        if (prod > 1) return ;
        res = min(res, make_pair(sumlog, cur));
        return ;
    }

    int bound = (i ? a[i-1] : nDiv);
    FORD(val,bound,1) if (prod % divs[val] == 0) {
        int k = divs[val] - 1;
        a[i] = val;

        attempt(i+1,
                prod / divs[val],
                sumlog + k * log(primes[i]),
                cur * power(primes[i], k) % MOD);
    }
}

bool isPrime(int n) {
    for(int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return n > 1;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);

    int n;
    while (GI(n) == 1) {
        res = make_pair((n-1) * log(3), power(3, n-1));

        nDiv = 0;
        for(int i = 1; i*i <= n; ++i) if (n % i == 0) {
            divs[++nDiv] = i;
            if (i*i != n) divs[++nDiv] = n / i;
        }
        sort(divs+1, divs+nDiv+1);

        attempt(0, n, 0.0, 1);
        cout << res.second << endl;
    }
}
