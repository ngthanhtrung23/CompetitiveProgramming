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

int f[10111], n, a, b, c;

int main() {
    cin >> n >> a >> b >> c;
    memset(f, -1, sizeof f);
    f[0] = 0;
    FOR(i,0,n)
    if (f[i] >= 0) {
        f[i+a] = max(f[i+a], f[i] + 1);
        f[i+b] = max(f[i+b], f[i] + 1);
        f[i+c] = max(f[i+c], f[i] + 1);
    }
    cout << f[n] << endl;
    return 0;
}
