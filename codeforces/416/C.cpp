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

struct Group {
    int size, money;
    int id;
} groups[1011];

struct Table {
    int size, id;
} tables[1011];

bool operator < (const Group &a, const Group &b) {
    return a.size < b.size;
}

bool operator < (const Table &a, const Table &b) {
    return a.size < b.size;
}

int nGroup, nTable;
int f[1011][1011];
pair<int,int> tr[1011][1011];

vector< pair<int,int> > res;

void trace(int i, int j) {
    if (i <= 0 || j <= 0) return ;
    if (tr[i][j].first == i-1 && tr[i][j].second == j-1) {
        res.push_back(make_pair(groups[i].id, tables[j].id));
    }
    trace(tr[i][j].first, tr[i][j].second);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> nGroup) {
        FOR(i,1,nGroup) {
            cin >> groups[i].size >> groups[i].money;
            groups[i].id = i;
        }
        cin >> nTable;
        FOR(i,1,nTable) {
            cin >> tables[i].size;
            tables[i].id = i;
        }
        sort(groups+1, groups+nGroup+1);
        sort(tables+1, tables+nTable+1);
        memset(tr, -1, sizeof tr);

        FOR(i,0,nGroup) FOR(j,0,nTable) {
            if (i == 0 || j == 0) f[i][j] = 0;
            else {
                f[i][j] = 0;
                if (groups[i].size <= tables[j].size) {
                    f[i][j] = f[i-1][j-1] + groups[i].money;
                    tr[i][j] = make_pair(i-1, j-1);
                }
                if (f[i-1][j] > f[i][j]) {
                    f[i][j] = f[i-1][j];
                    tr[i][j] = make_pair(i-1, j);
                }
                if (f[i][j-1] > f[i][j]) {
                    f[i][j] = f[i][j-1];
                    tr[i][j] = make_pair(i, j-1);
                }
            }
        }
        res.clear();
        trace(nGroup, nTable);
        cout << res.size() << ' ' << f[nGroup][nTable] << endl;
        REP(i,res.size()) cout << res[i].first << ' ' << res[i].second << endl;
    }
    return 0;
}

