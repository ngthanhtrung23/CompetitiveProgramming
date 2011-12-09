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

int a[100111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int ln = 0;
    int n; scanf("%d", &n);
    FOR(i,1,n) {
        scanf("%d", &a[i]);
        ln = max(ln, a[i]);
    }
    FOR(i,1,n) if (a[i] == ln) {
        if (a[i] != 1) a[i] = 1;
        else a[i] = 2;
        break;
    }
    sort(a + 1, a + n + 1);
    FOR(i,1,n) printf("%d ", a[i]);
    return 0;
}
