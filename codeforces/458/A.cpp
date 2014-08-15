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

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

char a[2][MN];
int cnt[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (gets(a[0]) && gets(a[1])) {
        memset(cnt, 0, sizeof cnt);
        REP(turn,2) {
            int l = strlen(a[turn]);
            REP(i,l) {
                if (a[turn][i] == '1') {
                    cnt[l-1-i] += (turn) ? -1 : 1;
                }
            }
        }

        bool found = false;
        FORD(i,100000,0) {
            if (cnt[i] >= 2) {
                cout << '>';
                found = true;
                break;
            } else if (cnt[i] <= -2) {
                cout << '<';
                found = true;
                break;
            }

            if (cnt[i]) {
                cnt[i-1] += cnt[i];
                cnt[i-2] += cnt[i];
            }
        }

        if (found) continue;

        double v = cnt[0] + cnt[1] * ((sqrt(5.0) + 1) / 2.0);
        if (v > 1e-9) cout << '>';
        else if (v < -1e-9) cout << '<';
        else cout << '=';
        cout << endl;
    }
    return 0;
}
