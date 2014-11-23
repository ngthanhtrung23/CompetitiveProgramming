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

// f(nstep, mask, bit9, p)
double f[2][256][2][311];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(10);
    int x, k, pp;
    while (cin >> x >> k >> pp) {
        double prob = pp / 100.0;
        prob = 1 - prob;
        memset(f, 0, sizeof f);

        int mask = x & 255;
        x >>= 8;
        int bit = x & 1, cnt = 0;
        while (x > 0 && x % 2 == bit) {
            ++cnt;
            x /= 2;
        }
        f[0][mask][bit][cnt] = 1.0;
        // cout << mask << ' ' << bit << ' ' << cnt << endl;

        int cur = 0;
        REP(turn,k) {
            memset(f[1-cur], 0, sizeof f[1-cur]);
            REP(mask,256) REP(bit,2) FOR(cnt,0,300)
            if (f[cur][mask][bit][cnt] >= 1e-20) {
                // add 1
                if (mask + 1 == 256) {
                    if (bit == 1) f[cur^1][0][0][cnt] += f[cur][mask][bit][cnt] * prob;
                    else f[cur^1][0][1][1] += f[cur][mask][bit][cnt] * prob;
                }
                else {
                    f[cur^1][mask+1][bit][cnt] += f[cur][mask][bit][cnt] * prob;
                }

                // mul 2
                int maxBit = (mask >= 128) ? 1 : 0;
                int newMask = (mask << 1) & 255;
                if (cnt == 0) {
                    if (maxBit == 0) f[cur^1][newMask][0][0] += f[cur][mask][bit][cnt] * (1 - prob);
                    else f[cur^1][newMask][1][1] += f[cur][mask][bit][cnt] * (1 - prob);
                }
                else if (maxBit == bit) {
                    f[cur^1][newMask][bit][cnt+1] += f[cur][mask][bit][cnt] * (1 - prob);
                }
                else {
                    f[cur^1][newMask][1-bit][1] += f[cur][mask][bit][cnt] * (1 - prob);
                }
            }
            cur = 1 - cur;
        }
        double res = 0;
        REP(mask,256) REP(bit,2) FOR(cnt,0,300) {
            if (mask == 0) {
                if (bit == 0) res += (8 + cnt) * f[cur][mask][bit][cnt];
                else res += 8 * f[cur][mask][bit][cnt];
            }
            else {
                int x = 0, s = mask;
                while ((s & 1) == 0) ++x, s >>= 1;
                res += x * f[cur][mask][bit][cnt];
            }
        }
        cout << res << endl;
    }
    return 0;
}

