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
using namespace std;

const double PI = acos(-1.0);
const int oo = 1000111000;

int n, a[20111], sum[20111];

int get(int k) {
    if (k < 3) return -oo;
    int res = -oo;
    int base = n / k;
    REP(i,base) sum[i] = 0;
    FOR(i,1,n) sum[i%base] += a[i];
    REP(i,base) res = max(res, sum[i]);
    return res;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1) {
        int res = 0;
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            res = res + a[i];
        }
        for(int i = 2; i*i <= n; i++) if (n % i == 0) {
            res = max(res, get(i));
            res = max(res, get(n / i));
        }
        printf("%d\n", res);
    }
    return 0;
}
