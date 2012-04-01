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

int rev(int x) {
    int res = 0;
    while (x) {
        res = (res * 10) + x % 10;
        x /= 10;
    }
    return res;
}

int sieve[1000111];

void init() {
    FOR(i,2,1000) if (!sieve[i]) {
        int j = i*i;
        while (j <= 1000000) {
            sieve[j] = 1;
            j += i;
        }
    }
    sieve[1] = 1;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    init();
    int n; cin >> n;
    int k = 0;
    FOR(i,2,1000000) if (!sieve[i] && !sieve[rev(i)] && rev(i) != i) {
        k++;
        if (k == n) {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}
