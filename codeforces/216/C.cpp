#include <sstream>
#include <iomanip>
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

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

int n, m, k;
int stop[11000111], sz;

int getStop(int u) {
    if (stop[sz] <= u) return sz;
    return lower_bound(stop+1, stop+sz+1, u+1) - stop - 1;
}

int get(int u) {
    return sz - getStop(u-1);
}

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        sz = 0;
        FOR(i,1,n+m) {
            while (get(i) < k || getStop(i) == sz) {
                ++sz;
                stop[sz] = i + n - 1;
            }
        }
        printf("%d\n", sz);
        FOR(i,1,sz) printf("%d ", stop[i] - n + 1); puts("");
    }
    return 0;
}