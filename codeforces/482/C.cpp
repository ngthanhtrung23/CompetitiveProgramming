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

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (S & TWO(X))

string a[55];
int n;
long long bad[TWO(20)];
double gt[55], f[55];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(12);
    gt[0] = 1;
    FOR(i,1,50) gt[i] = gt[i-1] * (double) i;

    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        int l = a[1].length();

        FOR(i,0,l-1) {
            f[i+1] = gt[i+1] / gt[l] * gt[l-i-1];
        }

        memset(bad, 0, sizeof bad);
        FOR(i,1,n) {
            // Assume string i is chosen
            FOR(j,1,n) if (i != j) {
                long long same = 0;
                REP(x,l) {
                    if (a[i][x] == a[j][x])
                        same |= TWO(x);
                }
                bad[same] |= TWO(i);
            }
        }

        FORD(S,TWO(l)-1,0)
            if (bad[S]) {
                REP(j,l) if (CONTAIN(S,j))
                    bad[S - TWO(j)] |= bad[S];
            }

        double res = 0.0;
        REP(S,TWO(l))
        REP(i,l)
            if (!CONTAIN(S,i)) {
                res += f[__builtin_popcountll(S) + 1] * __builtin_popcountll(bad[S] - bad[S+TWO(i)]) / (double) n;
            }
        cout << res << endl;
    }
    return 0;
}
