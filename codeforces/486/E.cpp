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

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
int n, a[MN], fEnd[MN], fStart[MN], bit[MN];

#define _(X) ((X) & (-(X)))
void update(int x, int val) {
    while (x < MN) bit[x] = max(bit[x], val), x += _(x);
}
int get(int x) {
    int res = 0;
    while (x > 0) res = max(res, bit[x]), x -= _(x);
    return res;
}

void reverse() {
    FOR(i,1,n) a[i] = 100001 - a[i];
}

vector<int> ls[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            fEnd[i] = get(a[i] - 1) + 1;
            update(a[i], fEnd[i]);
        }
        // PR(fEnd, n);

        memset(bit, 0, sizeof bit);
        reverse();
        FORD(i,n,1) {
            fStart[i] = get(a[i] - 1) +1;
            update(a[i], fStart[i]);
        }
        // PR(fStart, n);
        int lis = *max_element(fEnd+1, fEnd+n+1);

        FOR(i,1,n) ls[i].clear();
        FOR(i,1,n) ls[fEnd[i]].push_back(fStart[i]);
        FOR(i,1,n) sort(ls[i].begin(), ls[i].end(), greater<int>());


        FOR(i,1,n) {
            if (fEnd[i] + fStart[i] - 1 == lis) {
                if (ls[fEnd[i]].size() > 1 && ls[fEnd[i]][1] == fStart[i]) cout << 2;
                else cout << 3;
            }
            else cout << 1;
        }
        cout << endl;
    }
    return 0;
}

