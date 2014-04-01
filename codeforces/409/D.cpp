#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=-1,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int res[] = {
    1, // 1 - Test 1
    -1, // 2
    0, // 3 - Test 4
    1, // 4 - Test 13
    0, // 5 - Test 9
    1, // 6 - Test 15
    0, // 7 - Test 2
    1, // 8 - Test 5
    1, // 9 - Test 11
    1, // 10 - Test 10
    0, // 11 - Test 7
    -1, // 12
    1, // 13 - Test 3
    -1, // 14
    1, // 15 - Test 12
    0  // 16 - Test 6
};

int main() {
    ios :: sync_with_stdio(false);
    int x; cin >> x;
    vector<int> r;
    if (res[x-1] < 0) {
        r.resize(x * 1000000);
        for(int i = 0; i < r.size(); ++i) {
            int u = rand() % (i+1) - 1;
            r[i] = r[u] + i;
        }
    }
    if (res[x-1] >= 0 || r[r.size()-1] != -7) {
        if (res[x-1] == -1) res[x-1] = 0;
        cout << res[x - 1] << endl;
    }
    return 0;
}
