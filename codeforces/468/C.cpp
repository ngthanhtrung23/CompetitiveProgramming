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

const int MN = 211;
long long a;
long long cnt[MN], f[MN];

void init() {
    cnt[0] = 1; f[0] = 0;
    FOR(i,1,200) {
        cnt[i] = cnt[i-1] * 10LL;
        f[i] = f[i-1] * 10LL + cnt[i-1] * 45LL;
    }
    // PR(f, 5);
}

long long cal(string s) {
    long long right = 0, res = 0, left = 0;

    // PR(f, 5);
    // PR(cnt, 5);

    FOR(i,0,s.length()-1) {
        int u = s[i] - '0';
        left = u;

        res += left * f[s.length()-i-1];
        res += cnt[s.length()-i-1] * (u-1) * (u) / 2;

        // DEBUG(res);
    }

    right = 1;

    long long p10 = 1;
    FORD(i,s.length()-1,0) {
        int u = s[i] - '0';
        res += right * u;

        right += p10 * u;
        p10 *= 10LL;

        // DEBUG(res);
    }
    return res;
}

long long cal(long long x) {
    stringstream ss; ss << x;
    return cal(ss.str());
}

long long digitSum(long long x) {
    long long res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);

    while (cin >> a) {
        init();

        long long l = 1, r = 20001110001110001LL, res = r;
        while (l <= r) {
            long long mid = (l + r) >> 1;
            if (cal(mid) >= a) {
                res = mid;
                r = mid - 1;
            } else l = mid + 1;
        }

        long long cur = cal(res);
        if (cur == a) {
            cout << 1 << ' ' << res << endl;
            continue;
        }

        l = 1, r = res;
        while (cur != a) {
            if (cur > a) {
                cur -= digitSum(l);
                ++l;
            } else {
                ++r;
                cur += digitSum(r);
            }
        }
        cout << l << ' ' << r << endl;
    }
    return 0;
}
