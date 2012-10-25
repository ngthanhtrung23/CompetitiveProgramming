#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; puts("");
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int sieve[1000111], cnt[1000111];

void init() {
    sieve[1] = 1;
    FOR(i,2,1000) if (!sieve[i]) {
        int j = i*i;
        while (j <= 1000000) {
            sieve[j] = i;
            j += i;
        }
    }
    cnt[1] = 0;
    FOR(i,2,1000000) {
        cnt[i] = cnt[i-1];
        if (sieve[i] == 0) ++cnt[i];
    }
}

int a, b, k;

bool check(int l) {
    FOR(x,a,b-l+1) {
        if (cnt[x+l-1] - cnt[x-1] < k) return false;
    }
    return true;
}

int main() {
    init();
    while (scanf("%d%d%d", &a, &b, &k) == 3) {
        int res = -1;
        int l = 0, r = b - a + 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        printf("%d\n", res);
    }
    return 0;
}
