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

const int MN = 2011;

int m, n, k;
char a[MN][MN];
pair<int,int> queries[MN];
int result[MN];
int f[MN][MN], row[MN][MN];
int toLeft[MN], toRight[MN];

int getLeftCell(int i, int j) {
    int l = 1, r = j, res = j;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (row[i][j] - row[i][mid-1] == 0) {
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return res;
}

int getRightCell(int i, int j) {
    int l = j, r = n, res = j;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (row[i][mid] - row[i][j-1] == 0) {
            res = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    return res;
}

bool check(int size, int u, int v) {
    if (size > m || size > n) return false;
    
    int top = u, bottom = u;
    while (top > 1 && a[top-1][v] == '.') --top;
    while (bottom < m && a[bottom+1][v] == '.') ++bottom;

    if (bottom - top + 1 < size) return false;

    // cout << "Opened cell: " << u << ' ' << v << endl;
    // cout << "   "; FOR(j,1,n) cout << j; cout << endl;
    // FOR(i,1,m) {
        // cout << i << "  ";
        // FOR(j,1,n) cout << a[i][j];
        // cout << endl;
    // }
    FOR(i,top,bottom) {
        toLeft[i] = getLeftCell(i, v);
        toRight[i] = getRightCell(i, v);

        // cout << "Row " << i << ": " << toLeft[i] << ' ' << toRight[i] << endl;
    }

    multiset<int> left, right;
    FOR(i,top,top+size-1) {
        left.insert(toLeft[i]);
        right.insert(toRight[i]);
    }
    if (*right.begin() - *left.rbegin() + 1 >= size) return true;

    FOR(i,top+size,bottom) {
        left.erase(left.find(toLeft[i-size]));
        right.erase(right.find(toRight[i-size]));

        left.insert(toLeft[i]);
        right.insert(toRight[i]);

        if (*right.begin() - *left.rbegin() + 1 >= size) return true;
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n >> k) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        FOR(i,1,k) {
            cin >> queries[i].first >> queries[i].second;
            a[queries[i].first][queries[i].second] = 'X';
        }

        // Algorithm: Calculate result in reversed order. So first, we add 'X' to all queried cells.
        // and calculate max square.
        memset(f, 0, sizeof f);
        int best = 0;
        FORD(i,m,1) FORD(j,n,1) {
            f[i][j] = (a[i][j] == 'X') ? 0 : min(min(f[i+1][j], f[i][j+1]), f[i+1][j+1]) + 1;
            best = max(best, f[i][j]);
        }

        FOR(i,1,m) {
            row[i][0] = 0;
            FOR(j,1,n) row[i][j] = row[i][j-1] + (a[i][j] == 'X' ? 1 : 0);
        }

        // Now go in reverse order. Change 'X' --> '.' and update result
        FORD(i,k,1) {
            result[i] = best;

            // Change 'X' --> '.'
            a[queries[i].first][queries[i].second] = '.';
            FOR(j,queries[i].second,n)
                row[queries[i].first][j] = row[queries[i].first][j-1] + (a[queries[i].first][j] == 'X' ? 1 : 0);

            // As long as we find a greater square, update best.
            while (check(best+1, queries[i].first, queries[i].second)) ++best;
        }

        FOR(i,1,k) cout << result[i] << "\n";
    }
    return 0;
}
