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

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

struct Line {
    long long a, b, c;
    void read() { cin >> a >> b >> c; }
};

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    Line l1, l2;
    l1.read(); l2.read();

    if (l1.a == 0 && l1.b == 0 && l1.c) {
        cout << 0 << endl;
        return 0;
    }
    if (l2.a == 0 && l2.b == 0 && l2.c) {
        cout << 0 << endl;
        return 0;
    }

    if (l1.a == 0 && l1.b == 0 && l1.c == 0) {
        cout << -1 << endl;
        return 0;
    }
    if (l2.a == 0 && l2.b == 0 && l2.c == 0) {
        cout << -1 << endl;
        return 0;
    }

    if (l1.a*l2.b == l1.b*l2.a) {
        if (l1.c*l2.a == l1.a*l2.c && l1.c*l2.b == l1.b*l2.c) cout << -1 << endl;
        else cout << 0 << endl;
    }
    else cout << 1 << endl;
    return 0;
}

