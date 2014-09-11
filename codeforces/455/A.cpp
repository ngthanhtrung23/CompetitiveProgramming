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

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;
int n;
long long cnt[MN], f[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) {
            int a; cin >> a;
            cnt[a]++;
        }
        f[0] = 0;
        f[1] = cnt[1];

        long long res = 0;
        FOR(i,2,100000) {
            f[i] = max(f[i-1], f[i-2] + cnt[i] * i);
            res = max(res, f[i]);
        }
        cout << res << endl;
    }
    return 0;
}

