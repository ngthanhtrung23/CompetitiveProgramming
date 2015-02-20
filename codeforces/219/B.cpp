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

const long double PI = acos((long double) -1.0);

long long lt[20];

int main() {
    lt[0] = 1; FOR(i,1,18) lt[i] = lt[i-1] * 10;
    long long p, d;
    while (cin >> p >> d) {
        bool ok = false;
        FORD(i,18,1) {
            long long need = p % lt[i] + 1;
            if (need == lt[i]) {
                cout << p <<endl;
                ok = true;
                break;
            }
            if (need <= d) {
                cout << p - need << endl;
                ok = true;
                break;
            }
        }
        if (!ok) {
            cout << p << endl;
        }
    }
    return 0;
}