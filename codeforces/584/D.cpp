
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

bool isPrime(int n) {
    for(int i = 2; i*i <= n; ++i)
        if (n % i == 0) return false;
    return n > 1;
}

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        if (isPrime(n)) {
            cout << 1 << endl << n << endl;
        }
        else if (isPrime(n-2)) {
            cout << 2 << endl << 2 << ' ' << n-2 << endl;
        }
        else {
            int last = n - 4;
            while (!isPrime(last)) last -= 2;

            int i = 2;
            for(; !isPrime(i) || !isPrime(n - last - i); ++i);

            cout << 3 << endl << last << ' ' << i << ' ' << n - last - i << endl;
        }
    }
}
