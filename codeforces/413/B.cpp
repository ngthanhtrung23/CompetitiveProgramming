#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int n, m, k, a[20111][11];
int indiv[20111], chat[20111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m >> k) {
        FOR(i,1,n) FOR(j,1,m) cin >> a[i][j];
        memset(chat, 0, sizeof chat);
        memset(indiv, 0, sizeof indiv);
        while (k--) {
            int u, x;
            cin >> u >> x;
            chat[x]++;
            indiv[u]--;
        }

        FOR(i,1,n) {
            int res = indiv[i];
            FOR(j,1,m) if (a[i][j]) res += chat[j];
            cout << res << ' ';
        }
        cout << endl;
    }
    return 0;
}
