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

struct Matching {
    int n;
    vector< vector<int> > ke;
    vector< bool > seen;
    vector< int > matchL, matchR;

    Matching(int n) : n(n), ke(n), seen(n, false), matchL(n, -1), matchR(n, -1) {
    }

    void addEdge(int u, int v) {
        ke[u].push_back(v);
    }

    bool bpm(int u) {
        for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v) {
            if (seen[*v]) continue;
            seen[*v] = true;

            if (matchR[*v] < 0 || bpm(matchR[*v])) {
                matchL[u] = *v;
                matchR[*v] = u;
                return true;
            }
        }
        return false;
    }

    int match() {
        int res = 0;
        for(int i = 0; i < n; ++i) {
            for(int i = 0; i < n; ++i) seen[i] = false;
            if (bpm(i)) ++res;
        }
        return res;
    }
};

bool has[511][511];
int n, m, id[511];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m) {
        memset(has, false, sizeof has);
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            has[u][v] = true;
        }
        int res = 1000111000;
        FOR(center,1,n) {
            int cur = 0;
            // Edges center --> u and u --> center
            FOR(i,1,n) {
                if (i == center) {
                    if (!has[center][center]) ++cur;
                }
                else {
                    if (!has[center][i]) ++cur;
                    if (!has[i][center]) ++cur;
                }
            }
            
            // Add edges so that vertices has in-deg = out-deg = 1 --> need to find bpm
            int nId = 0, nEdges = 0;
            Matching mat(n-1);
            FOR(i,1,n) if (i != center) id[i] = nId++;
            FOR(i,1,n) FOR(j,1,n)
                if (i != center && j != center) {
                    if (has[i][j]) {
                        ++nEdges;
                        mat.addEdge(id[i], id[j]);
                    }
                }
            int max_match = mat.match();

            // Remove all edges that is not on bpm
            cur += nEdges - max_match;

            // Add edges that are missing from bpm
            cur += (n-1) - max_match;

            res = min(res, cur);
        }
        cout << res << endl;
    }
    return 0;
}

