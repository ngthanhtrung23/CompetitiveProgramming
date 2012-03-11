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

pair<int,int> a[100111];
int b[100111], k;
pair<int,int> res[100111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int x, y, u;
    int n, m; scanf("%d%d%d%d", &n, &m, &x, &y);
    FOR(i,1,n) {
        scanf("%d", &u);
        a[i] = MP(u-x, u+y);
    }
    FOR(i,1,m) scanf("%d", &b[i]);
    k = 0;
    int j = 1;
    FOR(i,1,n) {
        while (j < m && b[j] < a[i].F) j++;
        if (j <= m && b[j] >= a[i].F && b[j] <= a[i].S) {
            k++;
            res[k] = MP(i, j);
            j++;
        }
    }
    printf("%d\n", k);
    FOR(i,1,k) printf("%d %d\n", res[i].F, res[i].S);
    return 0;
}
