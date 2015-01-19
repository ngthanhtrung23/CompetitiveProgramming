#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

struct Node {
    int child[30];
} nodes[1000111];
int root, n, nNodes;

int addNode() {
    memset(nodes[nNodes].child, 0, sizeof nodes[nNodes]);
    return nNodes++;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cerr << "test = " << test << endl;
        nNodes = 0;
        root = addNode();

        cin >> n;
        int res = 0;
        while (n--) {
            string s; cin >> s;
            int p = root;
            int cur = s.length();

            REP(id,s.size()) {
                int x = s[id] - 'a';
                if (!nodes[p].child[x]) {
                    nodes[p].child[x] = addNode();
                    cur = min(cur, id+1);
                }
                p = nodes[p].child[x];
            }

            res += cur;
        }
        cerr << nNodes << endl;
        cout << "Case #" << test << ": " << res << endl;
    }
    return 0;
}

