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

int n, k;
map<string,int> m;
int a[111], b[111];

int main() {
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];
        m.clear();
        while (k--) {
            string s; cin >> s;
            m[s]++;
        }
        k = 0;
        for(map<string,int> :: iterator it = m.begin(); it != m.end(); it++)
            b[++k] = -it->S;

        sort(a+1, a+n+1);
        sort(b+1, b+k+1);
        FOR(i,1,k) b[i] = -b[i];

        // PR(a, n);
        // PR(b, k);

        int res = 0;
        FOR(i,1,k) {
            res += a[i]*b[i];
        }
        printf("%d ", res);

        res = 0;
        FORD(i,k,1) {
            res += a[n-i+1]*b[i];
        }
        printf("%d\n", res);
    }
    return 0;
}