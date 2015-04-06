
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

long long nextp10(long long m) {
    long long res = 1;
    while (res <= m) res *= 10LL;
    return res;
}

long long len(long long n) {
    if (n == 0) return 1;
    int res = 0;
    while (n > 0) {
        ++res;
        n /= 10;
    }
    return res;
}

int main() {
    long long w, m, k;
    while (cin >> w >> m >> k) {
        w /= k;
        --m;
        long long savem = m;
        while (w > 0) {
            long long p10 = nextp10(m) - 1;
            if (m == 0) p10 = 9;
            long long l = len(m);

            if (m == 0 || m < p10) {
                long long need = l * (p10 - m);
                if (w >= need) {
                    m = p10;
                    w -= need;
                }
                else {
                    long long can = w / l;
                    m = m + can;
                    w = 0;
                }
            }
            else {
                long long need = l + 1;
                if (w >= need) {
                    w -= need;
                    ++m;
                }
                else {
                    w = 0;
                    break;
                }
            }
        }
        cout << m - savem << endl;
    }
    return 0;
}

