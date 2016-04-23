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

pair<int,int> a[2011];
int res[2011];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k;
    while (scanf("%d%d", &k, &n) == 2) {
        FOR(i,1,n) {
            scanf("%d", &a[i].F);
            a[i].S = i;
            res[i] = 0;
        }
        sort(a+1, a+n+1);
        
        FOR(i,1,n) {
            if (k <= 0) break;
            res[a[i].S] = min(a[i].F, k);
            k -= min(a[i].F, k);
        }
        FOR(i,1,n) printf("%d ", res[i]);
        puts("");
    }
    return 0;
}