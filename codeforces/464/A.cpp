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

int n, p;
string a, b;

bool find(int cur, bool greater) {
    if (cur >= a.length()) {
        return greater;
    }

    FOR(c,'a','a' + p - 1) {
        if (cur > 0 && c == b[cur-1]) continue;
        if (cur > 1 && c == b[cur-2]) continue;
        if (!greater && c < a[cur]) continue;

        b[cur] = c;
        if (find(cur + 1, greater || c > a[cur])) return true;
        b[cur] = ' ';
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> p >> a) {
        bool ok = false;
        FORD(keep,n-1,0) {
            b = a.substr(0, keep);
            while (b.length() < a.length()) b += ' ';
            if (find(keep, false)) {
                cout << b << endl;
                ok = true;
                break;
            }
        }
        if (!ok) cout << "NO" << endl;
    }
    return 0;
}
