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

int sieve[100111];

void init() {
    FOR(i,2,1000) if (!sieve[i]) {
        int j = i*i;
        while (j <= 100000) {
            sieve[j] = 1;
            j += i;
        }
    }
}

vector<int> need;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ll k;
    init();
    while (cin >> k) {
        if (k == 1) {
            puts("1");
            puts("1");
            continue;
        }
        ll sum = 0;
        need.clear();
        FOR(i,2,100000) if (!sieve[i] && k % i == 0) {
            ll cur = 1;
            while (k % i == 0) {
                cur *= i;
                k /= i;
            }
            need.PB(cur);
            sum += cur;
        }
        if (k > 1 || sum > 100000) {
            puts("No solution");
            continue;
        }
        int cur = 0;
        printf("%d\n", (int)sum);
        REP(i,need.size()) {
            int x = need[i];
            FOR(t,2,x) {
                printf("%d ", cur + t);
            }
            printf("%d ", cur + 1);
            cur += x;
        }
        puts("");
    }
    return 0;
}
