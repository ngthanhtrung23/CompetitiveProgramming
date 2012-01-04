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

int n, a[111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n; scanf("%d", &n);
    FOR(i,1,n) scanf("%d", &a[i]);
    sort(a+1, a+n+1);
    int passed = 10;
    int res = 0, p = 0;
    FOR(i,1,n) {
        int nn = passed + a[i];
        if (nn <= 720) {
            res++;
            if (nn <= 360) p += 0;
            else p += nn - 360;
            passed += a[i];
        }
    }
    printf("%d %d\n", res, p);
    return 0;
}
