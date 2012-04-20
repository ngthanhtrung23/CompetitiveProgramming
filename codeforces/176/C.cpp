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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
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
    int n, m, x1, y1, x2, y2;
    while (cin >> m >> n >> x1 >> y1 >> x2 >> y2) {
        if (abs(x1-x2) >= 5 || abs(y1-y2) >= 5) puts("Second");
        else {
            int u = abs(x1 - x2), v = abs(y1 - y2);
            if (u == 3 && v == 4) puts("Second");
            else if (u == 4 && v == 3) puts("Second");
            else if (u == 4 && v == 4) puts("Second");
            else puts("First");
        }
    }
    return 0;
}
