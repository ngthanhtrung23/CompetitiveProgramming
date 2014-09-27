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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int n, res[111];
struct Query {
    int l, r;
    set<int> ans;
} queries[111];
int nQuery;

int diff(const set<int> & a, const set<int> &b) {
    for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
        if (!b.count(*it)) return *it;
    return -1;
}

int getAll() {
    for(__typeof(queries[1].ans.begin()) it = queries[1].ans.begin(); it != queries[1].ans.end(); ++it) {
        bool ok = true;
        for(int x = 2; x <= nQuery; ++x)
            if (!queries[x].ans.count(*it)) {
                ok = false;
                break;
            }
        if (ok) return *it;
    }
    return -1;
}

int getNeverAppear() {
    FOR(i,1,n) {
        bool ok = true;
        FOR(x,1,nQuery)
            if (queries[x].ans.count(i)) {
                ok = false;
                break;
            }
        if (ok) return i;
    }
    return -1;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        nQuery = n / 2 + n % 2;
        int each = nQuery;
        FOR(i,1,nQuery) {
            queries[i].l = i;
            queries[i].r = i + each - 1;
            cout << "Q " << queries[i].l << ' ' << queries[i].r << endl;
            queries[i].ans.clear();

            int u;
            FOR(x,queries[i].l,queries[i].r) {
                cin >> u;
                queries[i].ans.insert(u);
            }
        }

        FOR(i,1,nQuery-1) {
            res[i] = diff(queries[i].ans, queries[i+1].ans);
        }
        int cur = nQuery;
        res[cur] = getAll();

        for(int i = 2; i <= nQuery; ++i, ++cur) {
            res[cur+1] = diff(queries[i].ans, queries[i-1].ans);
        }

        if (n % 2 == 0) {
            res[n] = getNeverAppear();
        }

        cout << "A ";
        FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}

