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

char s[1000111];
int a[1000111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n1 = 0; ll res = 0;
    int k; scanf("%d\n", &k);
    gets(s); int n = strlen(s);
    int cur = 0;
    REP(i,n) {
        if (s[i] == '1') {
            n1++;
            a[n1] = cur;
            cur = 0;
        }
        else cur++;
    }
    n1++; a[n1] = cur;
    if (k == 0) {
        FOR(i,1,n1) res += a[i] * (ll) (a[i] + 1) / 2;
        cout << res;
        return 0;
    }
    
    FOR(i,1,n1) a[i]++;
    FOR(start,1,n1-k) {
        res += a[start] * (ll) a[start+k];
    }
    cout << res;
    return 0;
}
