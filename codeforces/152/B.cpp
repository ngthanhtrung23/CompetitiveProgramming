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

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    long long res = 0;
    int n, m; scanf("%d%d", &n, &m);
    int x, y; scanf("%d%d", &x, &y);
    int k; scanf("%d", &k);
    while (k--) {
        long long fx, fy;
        int dx, dy; scanf("%d%d", &dx, &dy);
        if (dx == 0) fx = 1000111000;
        else if (dx > 0) {
            fx = (n - x) / dx;
        }
        else { // dx < 0
            fx = (1 - x) / dx;
        }
        if (dy == 0) fy = 1000111000;
        else if (dy > 0) {
            fy = (m - y) / dy;
        }
        else {
            fy = (1 - y) / dy;
        }
        
        res += min(fx, fy);
        x += dx * min(fx, fy);
        y += dy * min(fx, fy);
//        cout << fx << ' ' << fy << endl;
    }
    cout << res;
    return 0;
}
