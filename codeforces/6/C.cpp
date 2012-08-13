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
const int MN = 100111;

int a[MN], l[MN], r[MN], n;

int main() {
    while (scanf("%d", &n) == 1) {
        r[n+1] = a[n+1] = 0;
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            l[i] = l[i-1] + a[i-1];
        }
        FORD(i,n,1) r[i] = r[i+1] + a[i+1];
        int c1 = 0, c2 = 0;
        FOR(i,1,n) {
            if (l[i] <= r[i]) ++c1;
            else ++c2;
        }
        cout << c1 << ' ' << c2 << endl;
    }
    return 0;
}
