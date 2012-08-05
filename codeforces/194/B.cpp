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
#define ll unsigned long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

ll gcd(ll a, ll b) {
    if (!b) return a;
    return gcd(b, a%b);
}

ll lcm(ll a, ll b) {
    return a*b / gcd(a, b);
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        ll n; cin >> n;
        cout << lcm(n+1, 4*n) / (n+1) + 1 << endl;
    }
    return 0;
}
