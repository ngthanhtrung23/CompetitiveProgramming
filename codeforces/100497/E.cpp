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

const int MN = 100111;
int l[MN], r[MN], st[MN], top, a[MN], n, k;
pair<long long, int> inc[MN];

long long sum(long long from, long long to) {
    if (from > to) swap(from, to);
    return (from + to) * (to - from + 1) / 2;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];
        top = 0; st[0] = 0;

        FOR(i,1,n) {
            while (top && a[st[top]] >= a[i]) --top;
            l[i] = st[top] + 1;
            st[++top] = i;
        }

        top = 0; st[0] = n + 1;
        FORD(i,n,1) {
            while (top && a[st[top]] >= a[i]) --top;
            r[i] = st[top] - 1;
            st[++top] = i;
        }

        FOR(i,1,n) {
            long long x = i - l[i] + 1;
            long long y = r[i] - i + 1;

            inc[i] = make_pair(y * sum(1, x) + x * sum(0, y-1), i);
        }

        sort(inc+1, inc+n+1);
        reverse(inc+1, inc+n+1);
        // FOR(i,1,n) cout << inc[i].first << ' ' << inc[i].second << endl;

        long long res = 0;
        FOR(i,1,n) {
            int can = (i <= k) ? 1 : 0;
            res += inc[i].first * (a[inc[i].second] + can);
        }
        cout << res << endl;
    }
    return 0;
}
