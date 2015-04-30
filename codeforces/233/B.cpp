
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

long long mySqrt(long long x) {
    long long y = round(sqrt(x));
    while (y*y < x) ++y;
    while (y*y > x) --y;
    return y;
}

bool isSquare(long long x) {
    long long y = mySqrt(x);
    return y*y == x;
}

bool hasSol;
long long res;

void update(long long x) {
    if (!hasSol) {
        res = x;
        hasSol = true;
    }
    else res = min(res, x);
}

int getSum(long long x) {
    int res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    long long n;
    while (cin >> n) {
        hasSol = false;
        REP(sum,100) {
            long long delta = sum*sum + 4*n;
            if (isSquare(delta)) {
                long long t = -sum - mySqrt(delta);
                if (t >= 0 && t % 2 == 0) {
                    long long x = t / 2;
                    if (getSum(x) == sum) {
                        update(x);
                    }
                }
                t = -sum + mySqrt(delta);
                if (t >= 0 && t % 2 == 0) {
                    long long x = t / 2;
                    if (getSum(x) == sum) update(x);
                }
            }
        }
        if (hasSol) cout << res << endl;
        else cout << -1 << endl;
    }
    return 0;
}
