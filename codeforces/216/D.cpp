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

int n;
vector<int> a[1011];

int get(int t, int l, int r) {
    if (l > a[t][a[t].size()-1]) return 0;
    if (r < a[t][0]) return 0;

    int i = lower_bound(a[t].begin(), a[t].end(), l) - a[t].begin();
    int j = upper_bound(a[t].begin(), a[t].end(), r) - a[t].begin() - 1;

    if (i > j) return 0;
    return j - i + 1;
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            a[i].clear();
            int k; scanf("%d", &k);
            a[i].resize(k);
            REP(x,k) scanf("%d", &a[i][x]);
            sort(a[i].begin(), a[i].end());
        }

        int res = 0;
        FOR(i,1,n) {
            REP(x,a[i].size()-1) {
                int l = a[i][x] + 1, r = a[i][x+1] - 1;
                if (l > r) continue;

                int ii = i + 1; if (ii > n) ii = 1;
                int u = get(ii, l, r);
                ii = i - 1; if (ii < 1) ii = n;
                int v = get(ii, l, r);

                if (u != v) ++res;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}