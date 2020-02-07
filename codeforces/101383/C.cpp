// Idea: there should be many 0-edges

#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
#define DEBUG(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }
#define PR0(A, n) { std::cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) std::cerr << A[_] << ' '; std::cerr << std::endl; }

#define REP(i, a) for (int i = 0; i < a; ++i)

struct DirectedDfs {
    int V;
    std::vector<int> num, low, current, S;
    int counter;
    std::vector< std::vector<int> > scc;
    std::vector< std::vector<int> > G;

    DirectedDfs(int V) : V(V), num(V, -1), low(V, 0), current(V, 0), counter(0) {
        G.resize(V);
    }

    void construct() {
        REP(i,V) if (num[i] == -1) dfs(i);
    }

    void addEdge(int u, int v) {
        G[u].push_back(v);
    }

    void dfs(int u) {
        low[u] = num[u] = counter++;
        S.push_back(u);
        current[u] = 1;
        for (int v : G[u]) {
            if (num[v] == -1) dfs(v);
            if (current[v]) low[u] = std::min(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            scc.push_back(std::vector<int>());
            while (1) {
                int v = S.back(); S.pop_back(); current[v] = 0;
                scc.back().push_back(v);
                if (u == v) break;
            }
        }
    }
};

int main() {
    freopen("floyd.in", "r", stdin);
    freopen("floyd.out", "w", stdout);
    
    int n; std::cin >> n;
    long long s; std::cin >> s;
    DirectedDfs graph(n);

    std::vector< std::vector<int> > d(n, std::vector<int> (n));
    REP(i,n) {
        REP(j,n) {
            if (i == j) continue;

            d[i][j] = s % 1000;
            s = s * 16807 % 2147483647LL;

            if (d[i][j] == 0) {
                graph.addEdge(i, j);
            }
        }
    }

    // map vertex to component ID.
    graph.construct();
    std::vector<int> compId(n);
    int nComp = graph.scc.size();
    REP(c, nComp) {
        auto& scc = graph.scc[c];
        for (auto v : scc) {
            compId[v] = c;
        }
    }

    std::vector<std::vector<int> > c(nComp, std::vector<int> (nComp, 1011));

    auto updMin = [] (int&f , int val) {
        if (val < f) f = val;
    };
    REP(i,n) REP(j,n) {
        int ci = compId[i];
        int cj = compId[j];
        updMin(c[ci][cj], d[i][j]);
    }

    // Floyd on new graph
    REP(k,nComp) REP(i,nComp) REP(j,nComp) {
        updMin(c[i][j], c[i][k] + c[k][j]);
    }

    long long r = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int ci = compId[i];
            int cj = compId[j];
            r = (r * 16807 + c[ci][cj]) % 2147483647LL;
        }
    }
    std::cout << r << '\n';
}
