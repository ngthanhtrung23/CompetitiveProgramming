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

#define left left_
#define right right_
const int MN = 311;
int m, n, a[MN][MN], T, tp, tu, td;
int left[MN][MN], right[MN][MN], up[MN][MN], down[MN][MN];

int go(int x, int y) {
    if (x == y) return tp;
    else if (x < y) return tu;
    else return td;
}

int go(int i, int j, int ii, int jj) {
    return go(a[i][j], a[ii][jj]);
}

int get(int i1, int i2, int j) {
    return up[i2][j] - up[i1][j] - right[i1][j] - left[i2][j];
}

int savei1, savei2, savej1, savej2;
void update(int &res, int cur, int i1, int i2, int j1, int j2) {
    if (abs(cur - T) < abs(res - T)) {
        res = cur;
        savei1 = i1;
        savei2 = i2;
        savej1 = j1;
        savej2 = j2;
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n >> T) {
        cin >> tp >> tu >> td;
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        FOR(i,1,m) FOR(j,1,n) {
            if (j > 1) right[i][j] = right[i][j-1] + go(i, j-1, i, j);
            if (j > 1) left[i][j] = left[i][j-1] + go(i, j, i, j-1);
            if (i > 1) up[i][j] = up[i-1][j] + go(i, j, i-1, j);
            if (i > 1) down[i][j] = down[i-1][j] + go(i-1, j, i, j);
        }
        int res = -1000111000;
        FOR(i1,1,m) FOR(i2,i1+2,m) {
            map<int, int> s;
            s.insert(make_pair(get(i1, i2, 1), 1));
            FOR(j,3,n) {
                int has = down[i2][j] - down[i1][j] + right[i1][j] + left[i2][j];
                auto it = s.lower_bound(T - has);
                if (it != s.end()) update(res, has + it->first, i1, i2, it->second, j);
                if (it != s.begin()) {
                    --it;
                    update(res, has + it->first, i1, i2, it->second, j);
                }
                s.insert(make_pair(get(i1, i2, j-1), j-1));
            }
        }
        // cout << res << endl;
        cout << savei1 << ' ' << savej1 << ' ' << savei2 << ' ' << savej2 << endl;
    }
    return 0;
}

