#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <queue>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define FORD(i,a,b) for(int i=(a), _b=(b); i >= _b; --i)
#define REP(i,a) for(int i = 0, _a=(a); i < _a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const int MN = 200111;

int n;
char a[MN], b[MN];
long long suma[MN], sumb[MN];

int main() {
    int n;
    while (scanf("%d\n", &n) == 1) {
        FOR(i,1,n) scanf("%c", &a[i]); scanf("\n");
        FOR(i,1,n) scanf("%c", &b[i]); scanf("\n");
        long double res = 0.0;

        FOR(c,'A','Z') {
            memset(suma, 0, sizeof suma);
            memset(sumb, 0, sizeof sumb);

            FORD(i,n,1) {
                suma[i] = suma[i+1];
                sumb[i] = sumb[i+1];
                if (a[i] == c) suma[i] += n - i + 1;
                if (b[i] == c) sumb[i] += n - i + 1;
            }

            FOR(i,1,n) {
                if (a[i] == c) res += i * sumb[i];
                if (b[i] == c) res += i * suma[i+1];
            }
        }

        long double sl = 0.0;
        FOR(l,1,n) sl += (n-l+1LL)*(n-l+1LL);
        cout << (fixed) << setprecision(8) << res / sl << endl;
    }
    return 0;
}
