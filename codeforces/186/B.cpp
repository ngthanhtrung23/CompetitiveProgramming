#include <sstream>
#include <iomanip>
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

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

int n, t1, t2, k;
pair<double, int> a[1011];

int main() {
    while (scanf("%d%d%d%d", &n, &t1, &t2, &k) == 4) {
        FOR(i,1,n) {
            int u, v; scanf("%d%d", &u, &v);
            if (u > v) swap(u,v);

            double cur = (u * t1) * (100-k) / (double) 100 + v * t2;
            cur = max(cur, (v*t1) * (100-k) / (double) 100 + u * t2);

            a[i] = MP(-cur, i);
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) printf("%d %.2lf\n", a[i].S, -a[i].F);
    }
    return 0;
}
