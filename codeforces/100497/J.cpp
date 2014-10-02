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

const int MN = 30111;

int n;
string a[MN];

struct Node {
    int next[33];
    vector<int> id;
} nodes[1000111];
int nNode;

map<string,int> id;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        id.clear();
        nNode = 0;
        FOR(i,1,n) {
            cin >> a[i];
            id[a[i]] = i;
            int p = 0;
            REP(x,a[i].length()) {
                int u = a[i][x] - 'a';
                if (!nodes[p].next[u]) {
                    nodes[p].next[u] = ++nNode;
                }
                p = nodes[p].next[u];
                nodes[p].id.push_back(i);
            }
        }

        int q; cin >> q;
        while (q--) {
            string s; cin >> s;
            int p = 0;
            int last = (id.count(s)) ? id[s] : n;
            int res = last;
            REP(i,s.length()) {
                int u = s[i] - 'a';
                if (!nodes[p].next[u]) break;
                p = nodes[p].next[u];

                if (last >= nodes[p].id.back()) res += nodes[p].id.size();
                else res += upper_bound(nodes[p].id.begin(), nodes[p].id.end(), last) - nodes[p].id.begin();
            }
            cout << res << endl;
        }

        REP(i,nNode+1) {
            memset(nodes[i].next, 0, sizeof nodes[i].next);
            nodes[i].id.clear();
        }
    }
    return 0;
}
