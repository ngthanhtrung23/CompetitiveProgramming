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

long long n, s;

long long getSum(long long from, long long to) {
    return (from + to) * (to - from + 1) / 2;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> s) {
        long long ln = 0, nn = 0;
        FOR(i,1,n-1) ln += i;
        FOR(i,1,n-1) nn -= i;

        if (s < nn || s > ln || abs(s % 2) != ln % 2) {
            cout << -1 << endl;
            continue;
        }

        long long cur = 0;
        cout << 0 << ' ';
        FOR(i,1,n-1) {
            long long has = n-1 - i + 1;

            ln = getSum(cur+1, cur+has);
            nn = getSum(cur-(has-2), cur+1);

            if (nn <= s && s <= ln) {
                s -= cur + 1;
                ++cur;
            } else {
                s -= cur - 1;
                --cur;
            }

            cout << cur << ' ';
        }
        cout << endl;
    }
    return 0;
}
