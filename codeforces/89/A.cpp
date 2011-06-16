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
#include <sstream>
#include <iomanip>

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

int n, m, k, a[10111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d %d %d", &n, &m, &k);
    FOR(i,1,n) scanf("%d", &a[i]);
    if (n % 2 == 0) puts("0");
    else {
        int req = n / 2 + 1;
        int each = m / req;
        ll all = each * (ll) k;
        for(int i = 1; i <= n; i += 2) all = min(all, (ll)a[i]);
        cout << all;
    }
    return 0;
}
