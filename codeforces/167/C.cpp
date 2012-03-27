//#pragma comment(linker, "/STACK:66777216")
#include <iomanip>
#include <sstream>
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
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int get(ll i, ll j) {
    if (i == 0 || j == 0) return 0;
    if (i == 1 || j == 1) return 1;
    
    if (i > j) swap(i,j);
    if (j / i >= i+1) {
        j %= i*(i+1LL);
    }
    if (j <= i) return 1;
    j %= 2*i;
    if (j >= i+i) return 1;
    if (j <= i) return 1;
    return 1-get(j-i,i);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        ll a, b; cin >> a >> b;
        if (get(a, b)) puts("First");
        else puts("Second");
    }
    return 0;
}
