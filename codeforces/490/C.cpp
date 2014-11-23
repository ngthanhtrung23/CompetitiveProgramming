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

const int MN = 1000111;
int n;
string s;
long long a, b;
long long l[MN], r[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        n = s.length(); s = " " + s;
        cin >> a >> b;

        FOR(i,1,n) l[i] = (l[i-1] * 10 + s[i] - '0') % a;
        r[n+1] = 0;
        long long p10 = 1;
        FORD(i,n,1) {
            r[i] = (r[i+1] + p10 * (s[i] - '0')) % b;
            p10 = (p10 * 10) % b;
        }

        // PR(l, n);
        // PR(r, n);

        bool ok = false;
        FOR(i,1,n-1) if (s[i+1] > '0' && l[i] == 0 && r[i+1] == 0) {
            cout << "YES" << endl;
            FOR(x,1,i) cout << s[x];
            cout << endl;
            FOR(x,i+1,n) cout << s[x];
            cout << endl;
            ok = true;
            break;
        }
        if (!ok) cout << "NO" << endl;
    }
    return 0;
}
