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

int res, m, n;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d%d", &m, &n);
    if (m > n) swap(m,n);
    if (m == 1) printf("%d\n", m*n);
    else if (m == 2 && n == 2) puts("4");
    else if (m == 2 && n % 2 == 1) printf("%d\n", n+1);
    else if (m == 2 && n % 4 == 0) printf("%d\n", n);
    else if (m == 2 && n % 4 == 2) printf("%d\n", n+2);
    else {
        int x = m*n / 2;
        printf("%d\n", max(x, m*n-x));
    }
    return 0;
}
