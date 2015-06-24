
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

int n, a[55];
long long k, fib[55];

void generate(int i, int prev, long long k) {
    if (i > n) return ;

    int len = n - i + 1;
    assert(fib[len] >= k);

    if (fib[len-1] >= k) {
        a[i] = i;
        generate(i+1, prev, k);
    }
    else {
        a[i] = i+1;
        a[i+1] = i;
        generate(i+2, prev, k - fib[len-1]);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    fib[0] = fib[1] = 1;
    FOR(i,2,50) fib[i] = fib[i-1] + fib[i-2];
    while (cin >> n >> k) {
        generate(1, 0, k);
        FOR(i,1,n) cout << a[i] << ' '; cout << endl;
    }
}
