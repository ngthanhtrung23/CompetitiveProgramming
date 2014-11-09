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

string s;
vector<int> ind[1000111];

#define hash hash_
int hash(string s) {
    int res = 0;
    REP(i,s.length())
        res = res * 27 + s[i] - 'a' + 1;
    return res;
}

void init() {
    REP(hash,1000111) ind[hash].clear();
    FOR(len,1,4) {
        FOR(i,0,s.length()-len) {
            string tmp = s.substr(i, len);
            ind[hash(tmp)].push_back(i);
        }
    }
}

int get(int u, int lx, int v, int ly) {
    return max(u + lx, v + ly) - min(u, v);
}

map< pair<int,int>, int > cache;
int query(int x, int y, int lx, int ly) {
    if (ind[x].empty() || ind[y].empty()) return -1;

    pair<int,int> xy = make_pair(x, y);
    if (cache.count(xy)) return cache[xy];

    int res = s.length();
    if (ind[x].size() > ind[y].size()) {
        swap(x, y);
        swap(lx, ly);
    }

    if ((ind[x].size() << 4) < ind[y].size()) {
        REP(it1,ind[x].size()) {
            int u = ind[x][it1];
            auto v = lower_bound(ind[y].begin(), ind[y].end(), u);
            if (v != ind[y].end()) res = min(res, get(u, lx, *v, ly));
            if (v != ind[y].begin()) {
                --v;
                res = min(res, get(u, lx, *v, ly));
            }
        }
    }
    else {
        int it2 = 0;
        REP(it1,ind[x].size()) {
            int u = ind[x][it1];
            while (it2 < ind[y].size()-1 && ind[y][it2] < u) ++it2;

            res = min(res, get(u, lx, ind[y][it2], ly));
            if (it2) res = min(res, get(u, lx, ind[y][it2-1], ly));
        }
    }

    return cache[xy] = res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        init();
        int q; cin >> q;
        cache.clear();
        while (q--) {
            string a, b;
            cin >> a >> b;
            cout << query(hash(a), hash(b), a.length(), b.length()) << "\n";
        }
    }
    return 0;
}
