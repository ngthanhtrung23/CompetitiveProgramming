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
const int MN = 100111;

int k, b, n;
int a[MN], s[MN];

long long solve0() {
    int i = 1;
    long long res = 0;
    while (i <= n) {
        if (a[i]) {
            ++i;
            continue;
        }
        else {
            int j = i;
            while (j < n && a[j+1] == 0) {
                ++j;
            }
            long long l = j - i + 1;
            res += l * (l+1) / 2;
            i = j + 1;
        }
    }
    return res;
}

map<int,int> m;

long long solve() {
    long long res = 0;
    m.clear();
    m[0] = 1;
    b %= (k-1);
    FOR(i,1,n) {
        int need = s[i] - b;
        if (need < 0) need += k-1;
        res += m[need];
        m[s[i]]++;
    }
    return res;
}

int main() {
    while (scanf("%d%d%d", &k, &b, &n) == 3) {
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            s[i] = (s[i-1] + a[i]) % (k-1);
        }
        // PR(s,n);
        long long res;
        if (b == 0) res = solve0();
        else if (b == k-1) res = solve() - solve0();
        else res = solve();
        cout << res << endl;
    }
    return 0;
}