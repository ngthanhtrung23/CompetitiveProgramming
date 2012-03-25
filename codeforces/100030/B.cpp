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

int f[111];
set<int> s;

void init() {
    f[1] = 0;
    FOR(i,2,40) {
        s.clear();
        FOR(j,1,i-1) {
            s.insert(f[j] ^ f[i-j]);
        }
        f[i] = 0;
        while (s.find(f[i]) != s.end()) f[i]++;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    init();
    int n;
    while (scanf("%d", &n) == 1) {
        int g = 0;
        FOR(i,1,n) {
            int a; scanf("%d", &a);
            g ^= f[a];
        }
        if (g) puts("Constantine");
        else puts("Mike");
    }
    return 0;
}
