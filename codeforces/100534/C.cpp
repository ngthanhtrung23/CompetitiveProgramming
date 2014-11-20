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

void addEdges(vector< pair<int,int> > &res, int need, int nLeaf) {
    int add = 0;
    FOR(i,1,nLeaf) FOR(j,i+1,nLeaf) {
        if (add >= need) return ;

        ++add;
        res.push_back(make_pair(i, j));
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int s;
    while (cin >> s) {
        if (s == 0) {
            cout << 1 << ' ' << 0 << endl;
        }
        else if (s == 2 || s == 5) {
            cout << "Impossible" << endl;
            continue;
        }
        else {
            int nLeaf = 1;
            while (nLeaf * nLeaf < s) ++nLeaf;
            
            int n = nLeaf + 1;
            vector< pair<int,int> > res;
            FOR(i,1,nLeaf) res.push_back(make_pair(n, i));

            int m = nLeaf * nLeaf;
            int need = m - s;
            addEdges(res, need, nLeaf);

            cout << n << ' ' << res.size() << endl;
            REP(i,res.size()) cout << res[i].first << ' ' << res[i].second << endl;
        }
    }
    return 0;
}
