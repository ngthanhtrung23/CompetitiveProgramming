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

const long double PI = acos((long double) -1.0);
const int MN = 100111;

int n, a[MN], b[MN];

int main() {
    scanf("%d", &n);
    FOR(i,1,n) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b+1, b+n+1);
    int cnt = 0;
    FOR(i,1,n) if (b[i] != a[i]) ++cnt;
    if (cnt <= 2) puts("YES"); else puts("NO");
    return 0;
}
