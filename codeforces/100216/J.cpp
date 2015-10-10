
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

const int inf = 1000111;
struct Matching {
    int n;
    vector<int> matchL, matchR, dist;
    vector<bool> seen;
    vector< vector<int> > ke;

    Matching(int n) : n(n), matchL(n+1), matchR(n+1), dist(n+1), seen(n+1, false), ke(n+1) {}

    void addEdge(int u, int v) {
        ke[u].push_back(v);
    }

    bool bfs() {
        queue<int> qu;
        for(int u = 1; u <= n; ++u)
            if (!matchL[u]) {
                dist[u] = 0;
                qu.push(u);
            } else dist[u] = inf;
        dist[0] = inf;

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v) {
                if (dist[matchR[*v]] == inf) {
                    dist[matchR[*v]] = dist[u] + 1;
                    qu.push(matchR[*v]);
                }
            }
        }
        return dist[0] != inf;
    }

    bool dfs(int u) {
        if (u) {
            for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v)
                if (dist[matchR[*v]] == dist[u] + 1 && dfs(matchR[*v])) {
                    matchL[u] = *v;
                    matchR[*v] = u;
                    return true;
                }
            dist[u] = inf;
            return false;
        }
        return true;
    }

    int match() {
        int res = 0;
        while (bfs()) {
            for(int u = 1; u <= n; ++u)
                if (!matchL[u])
                    if (dfs(u)) ++res;
        }
        return res;
    }
};

map<string,int> id;
int nReq, nFlight;
pair<int,int> req[511], flight[20111];
int getIn[2011], getOut[2011];
map<int,int> edge_id[50111];
vector<int> ans[511];

bool leftSide[50111], rightSide[50111];

void init() {
    id.clear();
    memset(getIn, 0, sizeof getIn);
    memset(getOut, 0, sizeof getOut);

    memset(leftSide, 0, sizeof leftSide);
    memset(rightSide, 0, sizeof rightSide);

    FOR(i,1,nReq) ans[i].clear();
    FOR(i,1,2*(nFlight + nReq)) edge_id[i].clear();
}

char tmp[1000111];
pair<string,string> getLine() {
    gets(tmp);
    string s(tmp);
    int comma = s.find(',');

    return make_pair(
            s.substr(0, comma),
            s.substr(comma+1)
            );
}

int getId(string s) {
    if (!id.count(s)) {
        int cur = SZ(id) + 1;
        id[s] = cur;
    }
    return id[s];
}

pair<int,int> read() {
    pair<string,string> a = getLine();
    return make_pair(getId(a.first), getId(a.second));
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("tickets.in", "r", stdin);
    freopen("tickets.out", "w", stdout);

    while (scanf("%d%d\n", &nReq, &nFlight) == 2) {
        init();
        try {
            FOR(i,1,nReq) {
                req[i] = read();

                if (leftSide[req[i].first]) throw 1;
                if (rightSide[req[i].second]) throw 1;
                leftSide[req[i].first] = rightSide[req[i].second] = true;
            }
        } catch (...) {
            puts("NO");
            continue;
        }
        int total_id = SZ(id);
        FOR(i,1,nFlight) {
            flight[i] = read();
            edge_id[flight[i].first][flight[i].second] = i;
            edge_id[flight[i].second][flight[i].first] = i;
        }
//        cout << "Requests: " << endl;
//        FOR(i,1,nReq) cout << req[i].first << ' ' << req[i].second << endl;
//        cout << "flights: " << endl;
//        FOR(i,1,nFlight) cout << flight[i].first << ' ' << flight[i].second << endl;

        Matching mat(max(nReq, SZ(id)));
        int need = 0;
        FOR(i,1,nReq) {
            int fr = req[i].first, to = req[i].second;
            if (!getIn[fr] && !getOut[to] && edge_id[fr].count(to)) {
                ans[i].push_back(edge_id[fr][to]);
                getIn[fr] = true;
                getOut[to] = true;
                edge_id[fr].erase(to);
                edge_id[to].erase(fr);
            }
            else {
                ++need;
                FOR(u,1,SZ(id)) if (!leftSide[u] && !rightSide[u]) {
                    if (edge_id[fr].count(u) && edge_id[u].count(to)
                            && !getIn[fr] && !getOut[u] && !getIn[u] && !getOut[to]) {
                        mat.addEdge(i, u);
                    }
                }
            }
        }
        int res = mat.match();
        if (res < need) {
            puts("NO");
        }
        else {
            puts("YES");
            FOR(i,1,nReq) if (ans[i].empty()) {
                int fr = req[i].first, u = mat.matchL[i], to = req[i].second;
                ans[i].push_back(edge_id[fr][u]);
                ans[i].push_back(edge_id[u][to]);
            }
            FOR(i,1,nReq) {
                printf("%d", SZ(ans[i]));
                for(int x : ans[i]) printf(" %d", x);
                puts("");
            }
        }
    }
}

