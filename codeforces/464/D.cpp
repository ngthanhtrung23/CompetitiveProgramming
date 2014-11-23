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

const int MAX_LEVEL = 600;
int n, k;
double f[2][MAX_LEVEL + 5];
double prob[2][MAX_LEVEL + 5];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(16);
    while (cin >> n >> k) {
        memset(f, 0, sizeof f);
        memset(prob, 0, sizeof prob);
        f[0][1] = 0.0;
        prob[0][1] = 1.0;

        int row = 0;
        FOR(i,0,n-1) {
            memset(f[row^1], 0, sizeof f[row^1]);
            memset(prob[row^1], 0, sizeof prob[row^1]);

            FOR(t,1,MAX_LEVEL) if (prob[row][t] > 1e-30) {
                double cur = prob[row][t] / (double) (t + 1) * (1 / (double) k);
                prob[row^1][t+1] += cur;
                f[row^1][t+1]    += cur * (f[row][t] / prob[row][t] + t);

                cur = prob[row][t] * t / (double) (t + 1) * (1 / (double) k);
                prob[row^1][t] += cur;
                f[row^1][t]    += cur * (f[row][t] / prob[row][t])
                                + (cur / t) * (t * (t + 1)) / 2.0;

                cur = prob[row][t] * (k - 1) / (double) k;
                prob[row^1][t] += cur;
                f[row^1][t]    += cur * (f[row][t] / prob[row][t]);
            }
            double sum = 0.0;
            FOR(t,1,MAX_LEVEL) sum += prob[row^1][t];

            FOR(t,1,MAX_LEVEL) prob[row^1][t] /= sum;

            row = 1 - row;
        }

        double res = 0.0;
        FOR(t,1,MAX_LEVEL)
            res += f[row][t];
        cout << res * k << endl;
    }
    return 0;
}

