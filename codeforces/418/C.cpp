#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

vector<int> gen(int n) {
    vector<int> res;
    if (n == 1) {
        res.push_back(1);
    }
    else if (n == 2) {
        res.push_back(3);
        res.push_back(4);
    }
    else {
        REP(i,n-1) res.push_back(2);
        res.push_back(n-2);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int m, n;
    while (cin >> m >> n) {
        vector<int> x = gen(n);
        vector<int> y = gen(m);

        FOR(i,1,m) {
            FOR(j,1,n) cout << y[i-1]*x[j-1] << ' ';
            cout << endl;
        }
    }
    return 0;
}
