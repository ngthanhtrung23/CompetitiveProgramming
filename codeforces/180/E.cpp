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
const int MN = 200111;

int a[MN], bit[MN], n, m, k;
vector<int> ls[MN];

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,1,m) ls[i].clear();
        memset(bit, 0, sizeof bit);

        FOR(i,1,n) ls[a[i]].PB(i);

        int res = 0;

        FOR(c,1,m) {
            int j = 0;
            REP(i,ls[c].size()) {
                while (j+1 < ls[c].size() && 
                        j+1 - i + 1 + k >= ls[c][j+1] - ls[c][i] + 1) ++j;
                res = max(res, j - i + 1);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
