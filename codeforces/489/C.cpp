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

bool can(int len, int sum) {
    if (len == 0) {
        if (sum == 0) return true;
        else return false;
    }
    if (sum > len * 9 || sum < 0) return false;
    else return true;
}

void nn(int len, int sum) {
    FOR(i,1,len) {
        FOR(cur,0,9)
        if (i > 1 || cur > 0)
        if (can(len-i, sum - cur)) {
            cout << cur;
            sum -= cur;
            break;
        }
    }
}
void ln(int len, int sum) {
    FOR(i,1,len) {
        FORD(cur,9,0)
        if (i > 1 || cur > 0)
        if (can(len-i, sum - cur)) {
            cout << cur;
            sum -= cur;
            break;
        }
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int len, sum;
    while (cin >> len >> sum) {
        if (len == 1 && sum == 0) {
            cout << 0 << ' ' << 0 << endl;
            continue;
        }
        if (sum == 0) {
            cout << -1 << ' ' << -1 << endl;
            continue;
        }
        if (!can(len, sum)) {
            cout << -1 << ' ' << -1 << endl;
            continue;
        }
        nn(len, sum); cout << ' ';
        ln(len, sum); cout << endl;
    }
    return 0;
}

