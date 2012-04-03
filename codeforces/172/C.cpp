
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
const int MN = 100111;

int res[MN];
int t[MN], x[MN], cnt[MN], n, m, bit[MN];

#define _(u) (u & (-u))
int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

void update(int u, int k) {
    while (u <= 10000) {
        bit[u] += k;
        u += _(u);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) scanf("%d%d", &t[i], &x[i]);
        
        int time = 0, ln = 0, first = 1, sum = 0;
        FOR(i,1,n) {
            ln = max(ln, x[i]);
            if (cnt[x[i]]) {
                sum -= 1 + (cnt[x[i]] >> 1);
                update(x[i], -1 - (cnt[x[i]] >> 1));
            }
            cnt[x[i]]++;
            sum += 1 + (cnt[x[i]] >> 1);
            update(x[i], 1 + (cnt[x[i]] >> 1));
            
            if (i % m == 0 || i == n) {
                time = max(time, t[i]);
                FOR(j,first,i) res[j] = time + x[j] + get(x[j] - 1);
                
                FOR(j,first,i) {
                    cnt[x[j]]--;
                    int now = get(x[j]) - get(x[j]-1);
                    if (now) {
                        update(x[j], -now);
                    }
                }
                time = time + (ln<<1) + sum;
                first = i + 1;
                ln = 0; sum = 0;
            }
        }
        FOR(i,1,n) printf("%d ", res[i]);
        puts("");
    }
    return 0;
}
