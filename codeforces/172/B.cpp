//#pragma comment(linker, "/STACK:66777216")
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
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int first[100111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int m, a, b, r;
    while (cin >> a >> b >> m >> r) {
        memset(first, 0, sizeof first);
        first[r] = 1;
        FOR(i,2,m*2) {
            r = (a * (ll)r + b) % m;
            if (first[r]) {
                printf("%d\n", i - first[r]);
                break;
            }
            first[r] = i;
        }
    }
    return 0;
}
