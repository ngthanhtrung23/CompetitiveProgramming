
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

string a[11];
bool visited[11][11], can[11][11];
pair<int,int> x[11];
int nx;
set<ll> all;

ll p[1011];
int id[11];

const int di[4] = {0,0,-1,1};
const int dj[4] = {-1,1,0,0};

void dfs(int u, int v) {
    visited[u][v] = true;
    REP(dir,4) {
        int uu = u + di[dir], vv = v + dj[dir];
        if (can[uu][vv] && !visited[uu][vv]) {
            dfs(uu, vv);
        }
    }
}

ll getHash(vector<pair<int,int> >& cur) {
    sort(cur.begin(), cur.end());
    ll res = 0;
    for(auto p : cur) {
        int dx = p.first - cur[0].first;
        int dy = p.second - cur[0].second;
        res = res * 71LL + dx + 1;
        res = res * 73LL + dy + 1;
    }
    return res;
}

vector< pair<int,int> > rotate(vector< pair<int,int> >& cur) {
    vector< pair<int,int> > res;
    for(auto p : cur) {
        res.push_back(make_pair(
                    p.second,
                    4 - p.first));
    }
    return res;
}
vector< pair<int,int> > flipx(vector< pair<int,int> >& cur) {
    vector< pair<int,int> > res;
    for(auto p : cur) {
        res.push_back(make_pair(
                    4 - p.first,
                    p.second));
    }
    return res;
}
vector< pair<int,int> > flipy(vector< pair<int,int> >& cur) {
    vector< pair<int,int> > res;
    for(auto p : cur) {
        res.push_back(make_pair(
                    p.first,
                    4 - p.second));
    }
    return res;
}

const ll BASE = 1e6 + 3;

void update(int nid) {
    vector<ll> t;
    FOR(val,1,nid) {
        // check connectivity
        memset(visited, 0, sizeof visited);
        memset(can, 0, sizeof can);

        vector< pair<int,int> > cur;
        FOR(i,1,nx) if (id[i] == val) {
            cur.push_back(x[i]);
            can[x[i].first][x[i].second] = 1;
        }

        dfs(cur[0].first, cur[0].second);
        for(auto p : cur)
            if (!visited[p.first][p.second]) return ;

        auto save = cur;

        ll h = 1e18;
        REP(rot,4) {
            REP(fx,2) {
                REP(fy,2) {
                    h = min(h, getHash(cur));
                    cur = flipy(cur);
                }
                cur = flipx(cur);
            }
            cur = rotate(cur);
        }
        t.push_back(h);
    }
    sort(t.begin(), t.end());

    ll res = 0;
    for(auto p : t) res = res * BASE + p;
    all.insert(res);
}

void attempt(int i, int nid) {
    if (i > nx) {
        update(nid);
        return ;
    }
    FOR(val,1,nid + 1) {
        id[i] = val;
        attempt(i+1, max(nid, val));
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("puzzle.in", "r", stdin);
    freopen("puzzle.out", "w", stdout);
    p[0] = 1; FOR(i,1,1000) p[i] = p[i-1] * 101;

    while (cin >> a[1] >> a[2]) {
        a[1] = " " + a[1] + " ";
        a[2] = " " + a[2] + " ";

        nx = 0;
        FOR(i,1,2) FOR(j,1,3) if (a[i][j] == '*') x[++nx] = make_pair(i, j);

        if (nx == 0) {
            cout << 1 << endl;
            continue;
        }

//        cout << "-----------" << endl;
//        FOR(i,1,nx) cout << x[i].first << ' ' << x[i].second << endl;

        memset(id, 0, sizeof id);
        all.clear();
        id[1] = 1;
        attempt(2, 1);
        cout << SZ(all) << endl;
    }
}
