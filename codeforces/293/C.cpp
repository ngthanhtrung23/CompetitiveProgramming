
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

long long n;
long long p[1011], k[1011], used[1011];
int np;
set< tuple<long long, long long, long long> > res;

void attempt2(int i, long long bc, long long ab) {
    if (i > np) {
        long long ca = n / ab / bc;
        long long abc = (ab + bc + ca) / 2;
        long long a = abc - bc;
        long long b = abc - ca;
        long long c = abc - ab;
        if (a > 0 && b > 0 && c > 0
                && (a + b) * (b + c) * (c + a) == n)
            res.insert(make_tuple(a, b, c));
        return ;
    }
    for(int power = 0, pp = 1; power <= k[i] - used[i]; power += 1, pp *= p[i]) {
        attempt2(i+1, bc * pp, ab);
    }
}

void attempt1(int i, long long ab) {
    if (i > np) {
        attempt2(1, 1LL, ab);
        return ;
    }

    for(int power=0, pp = 1; power <= k[i]; power += 1, pp *= p[i]) {
        used[i] = power;
        attempt1(i+1, ab * pp);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
//        cout << "-----------------\n";
        if (n % 3) {
            cout << 0 << endl;
            continue;
        }
        n /= 3;
//        DEBUG(n);
        long long saven = n;
        np = 0;
        for(long long i = 2; i <= 10111000; ++i)
            if (n % i == 0) {
                ++np;
                p[np] = i;
                k[np] = 0;
                while (n % i == 0) {
                    n /= i;
                    ++k[np];
                }
            }
        if (n > 1) {
            ++np;
            p[np] = n;
            k[np] = 1;
        }
//        PR(p, np);
//        PR(k, np);

        n = saven;

        res.clear();
        attempt1(1, 1LL);
        cout << res.size() << endl;
    }
    return 0;
}

