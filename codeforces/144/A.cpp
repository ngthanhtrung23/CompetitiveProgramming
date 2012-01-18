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

int a[111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n; scanf("%d", &n);
    FOR(i,1,n) scanf("%d", &a[i]);
    int nn = a[1], ln = a[1];
    FOR(i,1,n) {
        nn = min(a[i], nn);
        ln = max(a[i], ln);
    }
    int res = 1000111000;
    FOR(i,1,n) FOR(j,1,n) if (i != j && a[i] == ln && a[j] == nn) {
        if (i < j) res = min(res, i - 1 + n - j);
        else res = min(res, i - 1 + n - j - 1);
    }
    printf("%d", res);
    return 0;
}
