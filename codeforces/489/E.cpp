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

int n;
int x[1011], b[1011], l, tr[1011];
double f[1011];

bool check(double res) {
    FOR(i,0,n) {
        if (i == 0) f[i] = 0;
        else {
            f[i] = 1e12;
            tr[i] = 1;
            FOR(j,0,i-1) if (f[j] < 1e11) {
                double cur = f[j] - res * b[i] + sqrt(fabs(x[i] - x[j] - l));
                if (cur < f[i]) {
                    f[i] = cur;
                    tr[i] = j;
                }
            }
        }
    }
    return f[n] <= 0;
}

vector<int> ans;
void trace(int n) {
    if (n == 0) return ;
    ans.push_back(n);
    trace(tr[n]);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> l) {
        FOR(i,1,n) cin >> x[i] >> b[i];
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        double l = 0, r = 1e6, res = r;
        REP(turn,50) {
            double mid = (l + r) / 2.0;
            if (check(mid)) {
                res = mid;
                r = mid;
            }
            else l = mid;
        }
        check(res);
        ans.clear();
        trace(n);
        reverse(ans.begin(), ans.end());
        REP(i,ans.size()) cout << ans[i] << ' '; cout << endl;
        break;
    }
    return 0;
}
