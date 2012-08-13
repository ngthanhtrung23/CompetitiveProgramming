
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

int n0, n1;
pair<int,int> a[2][MN];
int s[2][MN];
int n, v;

int main() {
    while (scanf("%d%d", &n, &v) == 2) {
        n0 = n1 = 0;
        FOR(i,1,n) {
            int t, u; scanf("%d%d", &t, &u);
            if (t == 1) a[0][++n0] = MP(u,i);
            else a[1][++n1] = MP(u,i);
        }
        sort(a[0]+1, a[0]+n0+1);
        sort(a[1]+1, a[1]+n1+1);

        s[0][n0+1] = 0; FORD(i,n0,1) s[0][i] = s[0][i+1] + a[0][i].F;
        s[1][n1+1] = 0; FORD(i,n1,1) s[1][i] = s[1][i+1] + a[1][i].F;

        int res = -1, save0, save1;
        FOR(k1,0,n1) {
            int now = s[1][n1+1-k1];
            int can = min(n0, v-2*k1);
            if (can < 0) continue;
            now += s[0][n0+1-can];
            if (now > res) {
                res = now;
                save0 = can;
                save1 = k1;
            }
        }
        printf("%d\n", res);
        FORD(i,n0,n0-save0+1) printf("%d ", a[0][i].S);
        FORD(i,n1,n1-save1+1) printf("%d ", a[1][i].S);
        puts("");
    }
    return 0;
}
