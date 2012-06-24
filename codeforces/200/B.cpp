#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <complex>

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(i,a) for(int i = 0; i < a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(x,n) cout << #x << " = "; FOR(__,1,n) cout << x[__] << ' '; puts("");
#define PR0(x,n) cout << #x << " = "; REP(__,n) cout << x[__] << ' '; puts("");
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int sum = 0;
        FOR(i,1,n) {
            int u; cin >> u;
            sum += u;
        }
        cout << (fixed) << setprecision(6) << sum / (long double) (n) << endl;
    }
    return 0;
}