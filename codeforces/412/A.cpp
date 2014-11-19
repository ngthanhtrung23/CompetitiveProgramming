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

int n, k;
string s;

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> k >> s) {
        s = " " + s;
        if (k - 1 < n - k) {
            while (k > 1) {
                cout << "LEFT" << endl;
                --k;
            }
            FOR(i,1,n) {
                cout << "PRINT " << s[i] << endl;
                if (i != n) cout << "RIGHT" << endl;
            }
        }
        else {
            while (k < n) {
                cout << "RIGHT" << endl;
                ++k;
            }
            FORD(i,n,1) {
                cout << "PRINT " << s[i] << endl;
                if (i != 1) cout << "LEFT" << endl;
            }
        }
    }
    return 0;
}

