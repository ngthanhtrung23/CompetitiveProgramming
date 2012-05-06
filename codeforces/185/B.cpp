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

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int S, a, b, c;
    while (cin >> S >> a >> b >> c) {
        if (!a && !b && !c) {
            puts("0.0 0.0 0.0");
        }
        else {
            long double x = S / (long double) (a + b + c) * a;
            long double y = S / (long double) (a + b + c) * b;
            long double z = S / (long double) (a + b + c) * c;
            cout << (fixed) << setprecision(10) << x << ' ' << y << ' ' << z << endl;
        }
    }
    return 0;
}
