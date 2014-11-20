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
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

char a[11], b[11], savea[11];

int main() {
    while (gets(a) && gets(b)) {
        savea[0] = a[0]; savea[1] = a[1];
        int res = 0;
        REP(turn,2) {
            a[0] = savea[0]; a[1] = savea[1];
            while (a[0] != b[0] || a[1] != b[1]) {
                if (a[0] < b[0]) {
                    if (turn == 1) putchar('R');
                    ++a[0];
                }
                else if (a[0] > b[0]) {
                    if (turn == 1) putchar('L');
                    --a[0];
                }
                if (a[1] < b[1]) {
                    if (turn == 1) putchar('U');
                    ++a[1];
                }
                else if (a[1] > b[1]) {
                    if (turn == 1) putchar('D');
                    --a[1];
                }
                if (turn == 1) puts("");
                else ++res;
            }
            if (turn == 0) printf("%d\n", res);
        }
    }
    return 0;
}