
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int n, l, m;
pair<int,int> edges[100111];
vector<int> ke[100111];

void solve(vector<int> id, vector< vector<int> > c) {
    if (SZ(id) == 1) return ;

//    PR0(id, SZ(id));
//    REP(i,SZ(c[i])) PR0(c[i], SZ(c[i]));

    int left = -1, right = -1, diam = -1;
    REP(i,SZ(id)) FOR(j,i+1,SZ(id)-1) {
        if (c[i][j] == 0) throw 100;
        if (c[i][j] > diam) {
            diam = c[i][j];
            left = i;
            right = j;
        }
    }
    if (diam <= 0) throw 1;

    vector< vector< pair<int,int> > > vertexAt;
    vertexAt.resize(diam + 1);

    vertexAt[0].push_back(make_pair(0, left));
    vertexAt[diam].push_back(make_pair(0, right));

    REP(i,SZ(id)) if (i != left && i != right) {
        int toLeft = c[i][left], toRight = c[i][right];
        if (toLeft + toRight < diam) throw 2;
        int h = toLeft + toRight - diam;
        if (h % 2 == 1) throw 3;

        h /= 2;
        vertexAt[toLeft - h].push_back(make_pair(h, i));
    }

    vector<int> addedVertex; addedVertex.resize(diam+2);
    REP(i,diam+1) {
        sort(vertexAt[i].begin(), vertexAt[i].end());
        if (vertexAt[i].empty() || vertexAt[i][0].first) {
            vertexAt[i].push_back(make_pair(0, -1));
            addedVertex[i] = ++n;
        }
        sort(vertexAt[i].begin(), vertexAt[i].end());
        // connect the chain
        if (i > 0) {
            int v = (vertexAt[i][0].second < 0) ? addedVertex[i] : id[vertexAt[i][0].second];
            int u = (vertexAt[i-1][0].second < 0) ? addedVertex[i-1] : id[vertexAt[i-1][0].second]; 
            edges[++m] = make_pair(u, v);
        }

        // generate next_id
        vector<int> next_id; next_id.resize(SZ(vertexAt[i]));
        REP(j,SZ(vertexAt[i])) {
            int u = vertexAt[i][j].second < 0 ? addedVertex[i] : id[vertexAt[i][j].second];
            next_id[j] = u;
        }

        // generate next_c
        vector< vector<int> > next_c; next_c.resize(SZ(vertexAt[i]));
        REP(j,SZ(next_c)) next_c[j].resize(SZ(vertexAt[i]));

        REP(j,SZ(vertexAt[i])) FOR(jj,j+1,SZ(vertexAt[i])-1) {
            next_c[jj][j] =
            next_c[j][jj] = (vertexAt[i][j].second < 0) ? vertexAt[i][jj].first
                            : c[ vertexAt[i][j].second ][ vertexAt[i][jj].second ];
        }
        solve(next_id, next_c);
    }
}

int visited[100111];

void dfs(int u, int fu) {
    REP(i,SZ(ke[u])) {
        int v = ke[u][i];
        if (v == fu) continue;

        visited[v] = visited[u] + 1;
        dfs(v, u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("restore.in", "r", stdin);
    freopen("restore.out", "w", stdout);
    while (cin >> l) {
        n = l;
        vector< vector<int> > c;
        vector<int> id;

        c.resize(n);
        REP(i,n) {
            id.push_back(i+1);
            c[i].resize(n);
            REP(j,n) cin >> c[i][j];
        }

        m = 0;
        try {
            solve(id, c);

            FOR(i,1,m) {
                int u = edges[i].first, v = edges[i].second;
                ke[u].push_back(v);
                ke[v].push_back(u);
            }
            FOR(i,1,l) {
                memset(visited, -1, sizeof visited);
                visited[i] = 0;
                dfs(i, -1);
                FOR(j,1,l) if (c[i-1][j-1] != visited[j]) throw 10;

                if (SZ(ke[i]) > 1) throw 11;
            }
            cout << n << endl;
            FOR(i,1,m) cout << edges[i].first << ' ' << edges[i].second << '\n';
        } catch (int e) {
            cout << -1 << endl;
        }
        FOR(i,1,n) ke[i].clear();
    }
}

