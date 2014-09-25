#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <complex>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = (1<<20) + 11;
const double PI = acos(-1.0);
typedef complex<double> base;
base a[3][MN];
int outN = 1<<20;

int rev[MN];
base wlen_pw[MN];
 
void eval(base a[], int n, bool invert) {
    for (int i=0; i<n; ++i)
        if (i < rev[i])
            swap (a[i], a[rev[i]]);
 
    for (int len=2; len<=n; len<<=1) {
        double ang = 2*PI/len * (invert?-1:+1);
        int len2 = len>>1;
 
        base wlen (cos(ang), sin(ang));
        wlen_pw[0] = base (1, 0);
        for (int i=1; i<len2; ++i)
            wlen_pw[i] = wlen_pw[i-1] * wlen;
 
        for (int i=0; i<n; i+=len) {
            base t,
                *pu = a+i,
                *pv = a+i+len2, 
                *pu_end = a+i+len2,
                *pw = wlen_pw;
            for (; pu!=pu_end; ++pu, ++pv, ++pw) {
                t = *pv * *pw;
                *pv = *pu - t;
                *pu += t;
            }
        }
    }
 
    if (invert)
        for (int i=0; i<n; ++i)
            a[i] /= n;
}
 
void calc_rev(int n, int log_n) {
    for (int i=0; i<n; ++i) {
        rev[i] = 0;
        for (int j=0; j<log_n; ++j)
            if (i & (1<<j))
                rev[i] |= 1<<(log_n-1-j);
    }
}

int cnt[500111], n;

long long solve() {
    eval(a[0], outN, false);
    eval(a[1], outN, false);
    FOR(i,0,outN) a[2][i]=a[0][i]*a[1][i];
    eval(a[2], outN, true);

    long long res = 0;
    FOR(i,0,outN-1) {
        int cur = (int) (a[2][i].real() + 1e-3);
        res += cnt[i % n] * (long long) cur;
    }

    return res;
}

long long x[500111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);
        outN = 0;
        FOR(i,1,n-1) {
            x[i] = i * (long long) (i) % n;
            cnt[x[i]]++;
            outN = max(outN, (int) x[i]);
        }

        int lg = 2;

        while ((1LL<<lg) <= outN) ++lg;
        outN = 1LL << (lg+1);

        calc_rev(outN, lg + 1);

        // PR(x, n-1);
        long long res = 0;
        FOR(i,1,n-1) {
            int sum = (x[i] + x[i]) % n;
            res += cnt[sum];
        }
        // DEBUG(res);

        FOR(i,0,500000)
            a[0][i] = a[1][i] = base(cnt[i], 0);

        res += solve();
        // DEBUG(res);
        cout << res / 2 << endl;
    }
    return 0;
}
