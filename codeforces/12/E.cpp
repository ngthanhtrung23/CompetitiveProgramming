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

int a[1011][1011];

int main() {
    int n;
    while (cin >> n) {
        memset(a, -1, sizeof a);
        FOR(i,1,n) a[i][i] = 0;
        int last = 1, sum = 2;
        FOR(v,1,n-1) {
            ++last; ++sum;
            FOR(i,1,last) {
                if (a[i][sum-i] < 0) a[i][sum-i] = v;
            }
        }
        {
            int j = 1;
            for(int i = 2; i < n; i += 2) {
                ++j;
                if (a[j][n] < 0) a[j][n] = a[n][j] = i;
            }
            for(int i = 1; i < n; i += 2) {
                ++j;
                if (a[j][n] < 0) a[j][n] = a[n][j] = i;
            }
        }
        int i = 2; sum = n + 1;
        FOR(v,1,n-4) {
            ++i; ++sum;
            FOR(r,i,n-1) {
                if (a[r][sum-r] < 0) a[r][sum-r] = v;
            }
        }

        FOR(i,1,n) {
            FOR(j,1,n) printf("%d ", a[i][j]);
            puts("");
        }
    }
    return 0;
}