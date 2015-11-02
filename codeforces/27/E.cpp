
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

int nPrime = 15;
ll primes[15] = {
    2, 3, 5, 7, 11,13,17,19,23,29,31,37,41,43,47
};
int bound[15];
ll res;
int n;

void attempt(int i, ll prod, ll uoc) {
    if (i == nPrime) {
        if (uoc == n) {
            res = min(res, prod);
        }
        return ;
    }
    for(ll p = 1, cnt = 1;
            uoc * cnt <= n && cnt-1 <= bound[i];
            p *= primes[i], ++cnt) {
        if (prod * p < 0) break;
        if (prod * p > res) break;
        if (n % (uoc * cnt) == 0) {
            attempt(i+1, prod * p, uoc * cnt);
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    const ll oo = 1000111000111000111LL;
    REP(i,15) {
        bound[i] = 0;
        ll cur = 1;
        while (cur * primes[i] <= oo) {
            cur *= primes[i];
            ++bound[i];
        }
    }
    while (cin >> n) {
        res = oo;
        attempt(0, 1, 1);
        cout << res << endl;
    }
}

