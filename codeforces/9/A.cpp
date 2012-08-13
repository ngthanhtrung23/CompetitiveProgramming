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

int gcd(int a, int b) {
    if (!a || !b) return a+b;
    return gcd(b, a%b);
}

int main() {
    int a, b;
    while (cin >> a >> b) {
        int tu = 0, mau = 6;
        FOR(i,1,6) {
            if (i >= a && i >= b) ++tu;
        }
        if (tu == 0) {
            puts("0/1");
            continue;
        }
        int g = gcd(tu, mau);
        tu /= g;
        mau /= g;
        cout << tu << '/' << mau << endl;
    }
    return 0;
}
