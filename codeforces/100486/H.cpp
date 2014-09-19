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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

char s[100111];
int op[111], val[111], n;
pair<long long, long long> f[111][111];

void update(pair<long long, long long> &f, long long val) {
    if (f.first < 0) f.first = val;
    else f.first = min(f.first, val);
    f.second = max(f.second, val);
}

int main() {
    ios :: sync_with_stdio(false);
    while (gets(s)) {
        if (!strcmp(s, "END")) break;

        n = 0;
        REP(i,strlen(s)) {
            if (s[i] == '+') {
                op[++n] = 0;
                s[i] = ' ';
            } else if (s[i] == '*') {
                op[++n] = 1;
                s[i] = ' ';
            }
        }

        istringstream ss(s);
        FOR(i,1,n+1) ss >> val[i];
        // PR(op, n);
        // PR(val, n+1);

        ++n;

        FOR(i,1,n) f[i][i] = make_pair(val[i], val[i]);
        FORD(i,n,1) FOR(j,i+1,n) {
            f[i][j] = make_pair(-1LL, -1LL);
            FOR(k,i,j-1) {
                if (op[k] == 0) {
                    update(f[i][j], f[i][k].first + f[k+1][j].first);
                    update(f[i][j], f[i][k].first + f[k+1][j].second);
                    update(f[i][j], f[i][k].second + f[k+1][j].first);
                    update(f[i][j], f[i][k].second + f[k+1][j].second);
                } else {
                    update(f[i][j], f[i][k].first * f[k+1][j].first);
                    update(f[i][j], f[i][k].first * f[k+1][j].second);
                    update(f[i][j], f[i][k].second * f[k+1][j].first);
                    update(f[i][j], f[i][k].second * f[k+1][j].second);
                }
            }
        }

        cout << f[1][n].first << ' ' << f[1][n].second << endl;
    }
    return 0;
}
