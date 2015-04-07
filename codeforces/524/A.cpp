
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

int n, k;
map<int,int> id;
int deg[1011];
int a[1011], b[1011], rev[1011];
int ke[1011][1011];
vector<int> res[1011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        id.clear();
        memset(deg, 0, sizeof deg);
        memset(rev, 0, sizeof rev);
        memset(ke, 0, sizeof ke);

        FOR(i,1,n) {
            cin >> a[i] >> b[i];
            id[a[i]] = 1;
            id[b[i]] = 1;
        }
        int cur = 0;
        for(auto p : id) {
            id[p.first] = ++cur;
            rev[cur] = p.first;
        }

        FOR(i,1,n) {
            a[i] = id[a[i]];
            b[i] = id[b[i]];
            deg[a[i]]++;
            deg[b[i]]++;
            ke[a[i]][b[i]] = ke[b[i]][a[i]] = 1;
        }
        for(auto p : id) {
            int x = id[p.first];
            res[x].clear();

            FOR(y,1,id.size()) if (y != x && !ke[x][y]) {
                int cur = 0;
                FOR(z,1,id.size())
                    if (ke[x][z] && ke[y][z]) ++cur;

                if (cur * 100 >= k * deg[x]) res[x].push_back(y);
            }

            cout << rev[x] << ": " << res[x].size();
            for(auto y : res[x]) cout << ' ' << rev[y];
            cout << endl;
        }
    }
    return 0;
}

