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
using namespace std;

const double PI = acos(-1.0);

int n, need, h, a[1011];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> need >> n >> h;
    FOR(i,1,n) cin >> a[i];
    int sum = 0;
    FOR(i,1,n) sum += a[i];
    if (sum < need) {
        puts("-1.0");
        return 0;
    }
    need--;
    a[h]--;
    sum--;
    if (sum - a[h] < need) {
        puts("1.0");
        return 0;
    }
    long double res = 1.0;
    for(int x = sum - a[h] - need + 1, y = sum - need + 1; x <= sum - a[h]; x++, y++)
        res = res * x / (long double) y;
    cout << (fixed) << setprecision(8) << 1.0 - res << endl;
    return 0;
}
