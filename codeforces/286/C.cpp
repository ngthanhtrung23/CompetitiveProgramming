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
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 1000111;
int n, a[MN];
bool bad[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(0);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        memset(bad, false, sizeof bad);
        int q; scanf("%d", &q);
        while (q--) { int u; scanf("%d", &u); bad[u] = true; }

        stack<int> st;
        FORD(i,n,1) {
            if (bad[i]) a[i] = -a[i];
            else if (!st.empty() && st.top() == a[i]) {
                a[i] = +a[i];
            }
            else {
                a[i] = -a[i];
            }

            if (a[i] > 0) st.pop();
            else st.push(-a[i]);
        }
        if (st.empty()) {
            puts("YES");
            FOR(i,1,n) printf("%d ", a[i]);
            puts("");
        }
        else puts("NO");
    }
    return 0;
}

