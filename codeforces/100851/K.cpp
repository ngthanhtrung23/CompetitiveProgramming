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
#define next next___
#define prev prev___
using namespace std;

const int MN = 100111;
int degIn[MN], degOut[MN];
pair<int,int> edges[MN];
bool used[MN];
bool inChain[MN];
int n, m;
int next[MN], prev[MN];

int nChain;
struct Chain {
    int getIn, getOut;
    vector<int> x;
} chains[MN];

vector<int> ke[MN]; // chain adjacency
int chainId[MN];
int path[MN], canEnd[MN], visited[MN];

set< pair<int,int> > allEdges;

int iterations;
void init() {
    allEdges.clear();
    memset(degIn, 0, sizeof degIn);
    memset(degOut, 0, sizeof degOut);
    memset(next, -1, sizeof next);
    memset(prev, -1, sizeof prev);
    memset(chainId, -1, sizeof chainId);
    memset(used, 0, sizeof used);
    memset(canEnd, 0, sizeof canEnd);
    memset(visited, 0, sizeof visited);
    memset(inChain, 0, sizeof inChain);

    nChain = 0;
    iterations = 0;

    FOR(i,1,n) {
        ke[i].clear();
        chains[i].x.clear();
    }
}

#define BAD { puts("There is no route, Karl!"); return ; }
void printResult(vector<int>& res) {
    if (SZ(res) != n) BAD;
    REP(i,SZ(res)) {
        int j = (i + 1) % SZ(res);
        if (!allEdges.count(make_pair(res[i], res[j]))) {
            BAD;
        }
    }
    REP(i,SZ(res)) if (res[i] == 1) {
        FOR(j,i,SZ(res)-1) printf("%d ", res[j]);
        FOR(j,0,i) printf("%d ", res[j]);
    }
    puts("");
}

void attempt(int turn) {
    if (turn > nChain) {
        vector<int> res;
        FOR(i,1,nChain) {
            int u = path[i];
            for(int orig : chains[u].x) {
                res.push_back(orig);
            }
        }
        printResult(res);
        throw 1; 
    }
    int last = path[turn - 1];
    for(int u : ke[last]) if (!visited[u]) {
        if (turn == nChain && !canEnd[u]) continue;

        path[turn] = u;
        visited[u] = true;
        attempt(turn+1);
        path[turn] = 0;
        visited[u] = false;
    }
}

void solve() {
//    ++iterations; if (iterations > 5111000) return ;
    if (m < n) BAD;

    // first step: compressing vertices
    bool hasEdge = false;
    FOR(i,1,m) {
        int u = edges[i].first, v = edges[i].second;
        if (degOut[u] == 1 || degIn[v] == 1) {
            hasEdge = true;
//            cout << u << ' ' << v << endl;
            // must use edge (u, v)
            if (next[u] < 0) next[u] = v;
            else BAD;

            if (prev[v] < 0) prev[v] = u;
            else BAD;
        }
    }
    FOR(i,1,n) if (prev[i] < 0) {
        // start of a chain
        ++nChain;
        int u = i;
        chains[nChain].getIn = u;
        chains[nChain].getOut = u;
        chains[nChain].x.push_back(u);
        inChain[u] = true;

        while (next[u] >= 0) {
            int v = next[u];
            if (inChain[v]) {
                if (v == u) break;
                BAD;
            }
            inChain[v] = true;
            u = v;

            chains[nChain].x.push_back(u);
            chains[nChain].getOut = u;
        }
//        PR0(chains[nChain].x, SZ(chains[nChain].x));
    }
//    if (n == 98890) cout << "DONE INIT CHAIN" << endl;
    if (nChain == 0 && hasEdge) {
        int u = 1;
        vector<int> res; res.push_back(u);
        while (next[u] != 1) {
            int v = next[u];
            u = v;
            res.push_back(u);
        }
        if (SZ(res) != n) {
            BAD;
        }
        else {
            printResult(res);
            return ;
        }
    }
//    if (n == 98890) cout << "DONE CYCLE CHECK" << endl;
    // create graph with chains
//    cout << "CHAIN GRAPH" << endl;
//    DEBUG(nChain);
    FOR(i,1,nChain) {
        chainId[chains[i].getIn] = i;
        chainId[chains[i].getOut] = i;
    }
    FOR(i,1,m) if (!used[i]) {
        int u = edges[i].first, v = edges[i].second;
        int cu = chainId[u], cv = chainId[v];
        if (cu < 0 || cv < 0) continue;

        if (u == chains[cu].getOut && v == chains[cv].getIn) {
//            cout << cu << ' ' << cv << endl;
            ke[cu].push_back(cv);

            if (cv == 1) canEnd[cu] = 1;
        }
    }
//    if (n == 98890) {
//        cout << "DONE CHAIN GRAPH" << endl;
//        DEBUG(nChain);
//        FOR(i,1,nChain) DEBUG(SZ(ke[i]));
//    }
    // brute force on chain

    if (nChain == 1) {
        if (!canEnd[1]) BAD;
        printResult(chains[1].x);
        return ;
    }
    FOR(i,1,nChain) if (SZ(ke[i]) == 0) BAD;

    path[1] = 1;
    visited[1] = true;
    try {
        attempt(2);
        BAD;
    } catch (int e) {
    }
}

int main() {
//    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("king.in", "r", stdin);
    freopen("king.out", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        init();
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            degOut[u]++;
            degIn[v]++;

            edges[i] = make_pair(u, v);
            allEdges.insert(make_pair(u, v));
        }
        solve();
    }
}
