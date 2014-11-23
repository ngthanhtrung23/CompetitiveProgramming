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

const int MN = 100111;
string a[MN];
int n;
bool can[MN];

void solve() {
    FOR(i,1,n) {
        if (a[i].length() < a[i-1].length()) {
            cout << "NO" << endl;
            return ;
        }
        else if (a[i].length() > a[i-1].length()) {
            REP(x,a[i].length())
                if (a[i][x] == '?') {
                    if (x == 0) a[i][x] = '1';
                    else a[i][x] = '0';
                }
        }
        else {
            int l = a[i].length();
            can[l] = false;
            FORD(x,l-1,0) {
                bool rev = false;
                if (a[i][x] == '?') {
                    a[i][x] = '9';
                    rev = true;
                }

                if (a[i][x] > a[i-1][x]) can[x] = true;
                else if (a[i][x] < a[i-1][x]) can[x] = false;
                else can[x] = can[x+1];

                if (rev) a[i][x] = '?';
            }

            if (!can[0]) {
                cout << "NO" << endl;
                return ;
            }

            bool greater = false;
            REP(x,l) {
                if (greater) {
                    if (a[i][x] == '?') {
                        a[i][x] = '0';
                    }
                    continue;
                }

                if (a[i][x] == '?') {
                    if (can[x+1]) a[i][x] = a[i-1][x];
                    else a[i][x] = a[i-1][x] + 1;
                }
                if (a[i][x] > a[i-1][x]) greater = true;
            }
        }
    }
    cout << "YES" << endl;
    FOR(i,1,n) cout << a[i] << "\n";
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        a[0] = "";
        solve();
    }
    return 0;
}
