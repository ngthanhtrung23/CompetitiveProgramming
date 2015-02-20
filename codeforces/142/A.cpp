
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

int main() {
    int n;
    while (cin >> n) {
        vector<int> divisors;
        for(int i = 1; i*i <= n; ++i)
            if (n % i == 0) {
                divisors.push_back(i);
                if (i * i != n) divisors.push_back(n / i);
            }
        sort(divisors.begin(), divisors.end());

//        PR0(divisors, divisors.size());

        ll nn = -1, ln = -1;
        FOR(i,0,divisors.size()-1)
            FOR(j,0,divisors.size()-1) {
                int a = divisors[i];
                int b = divisors[j];
                if ((n / a) % b == 0) {
                    int c = n / a / b;

                    ll old = (a + 1LL) * (b + 2LL) * (c + 2LL);
                    ll now = old - n;

                    if (nn < 0) nn = now; else nn = min(nn, now);
                    if (ln < 0) ln = now; else ln = max(ln, now);
                }
            }

        cout << nn << ' ' << ln << endl;
    }
    return 0;
}
