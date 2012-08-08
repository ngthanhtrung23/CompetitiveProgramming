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
const int BASE = 1000000007;

int ntest;
char a[111];
int f[111][4000];

void update(int &a, int b) {
    a += b;
    if (a >= BASE) a -= BASE;
}

int main() {
    f[0][0] = 1;
    FOR(i,0,99) FOR(sum,0,3000) if (f[i][sum]) {
        FOR(add,0,25) {
            update(f[i+1][sum+add], f[i][sum]);
        }
    }
    while (scanf("%d\n", &ntest) == 1) {
        while (ntest--) {
            memset(a, 0, sizeof a);
            gets(a);
            int n = strlen(a);
            int sum = 0;
            REP(i,n) sum += a[i] - 'a';
            printf("%d\n", (f[n][sum] + BASE - 1) % BASE);
        }
    }
    return 0;
}
