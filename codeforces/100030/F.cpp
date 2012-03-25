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

map<ll,int> m;
ll p[20], sum[60111];
int n, tr[60111], qu[60111], d[60111];
char s[60111][20];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (scanf("%d\n", &n) == 1) {
        m.clear();
        FOR(i,1,n) {
            gets(s[i]);
            sum[i] = 0;
            int l = strlen(s[i]);
            REP(x,l) sum[i] = sum[i] * 27LL + (s[i][x] - 'a');
            m[sum[i]] = i;
        }
        int l = strlen(s[1]);
        p[l-1] = 1;
        FORD(i,l-2,0) p[i] = p[i+1] * 27LL;
        
        int first = 1, last = 1; qu[1] = n;
        memset(d, -1, sizeof d);
        d[n] = 1;
        memset(tr, 0, sizeof tr);
        while (first <= last) {
            int u = qu[first++];
            ll next;
            REP(i,l) FOR(cur,'a','z') if (cur != s[u][i]) {
                next = sum[u] - s[u][i] * p[i] + cur * p[i];
                if (m.find(next) != m.end()) {
                    int v = m[next];
                    if (d[v] < 0) {
                        d[v] = d[u] + 1;
                        tr[v] = u;
                        qu[++last] = v;
                    }
                }
            }
        }
        if (d[1] < 0) {
            puts("FAIL");
            continue;
        }
        printf("%d\n", d[1]);
        int u = 1;
        while (u != n) {
            puts(s[u]);
            u = tr[u];
        }
        puts(s[n]);
    }
    return 0;
}
