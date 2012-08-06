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

string a, b;

int main() {
    ios :: sync_with_stdio(false);
    cin >> a >> b;
    if (a.length() != b.length()) {
        puts("NO");
        return 0;
    }
    int n = a.length();
    int first, second, cnt = 0;

    REP(i,n) if (a[i] != b[i]) {
        ++cnt;
        if (cnt == 1) first = i;
        else if (cnt == 2) second = i;
    }
    if (cnt != 2) {
        puts("NO");
        return 0;
    }
    if (a[first] != b[second] || a[second] != b[first]) {
        puts("NO");
        return 0;
    }
    puts("YES");
    return 0;
}
