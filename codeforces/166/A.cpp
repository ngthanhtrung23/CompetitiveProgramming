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

pair< pair<int,int>, int > a[55];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, k; scanf("%d%d", &n, &k);
    FOR(i,1,n) {
        scanf("%d%d", &a[i].F.F, &a[i].F.S);
        a[i].S = i;
        a[i].F.F = -a[i].F.F;
    }
    sort(a+1, a+n+1);
    int cnt = 0;
    FOR(i,1,n) if (a[i].F == a[k].F) cnt++;
    printf("%d", cnt);
    return 0;
}
