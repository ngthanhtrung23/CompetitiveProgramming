#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,N)  { cout << #A << " = "; FOR(_,1,N) cout << A[_] << ' '; cout << endl; }
#define PR0(A,N) { cout << #A << " = "; REP(_,N) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;
#define int long long

const int MN = 33;
#define arg __arg
int N;
const int inf = 1e15;
long long c[MN][MN];
long long fx[MN], fy[MN];
int mx[MN], my[MN];
int trace[MN], qu[MN], arg[MN];
long long d[MN];
int front, rear, start, finish;

void init() {
    FOR(i,1,N) {
        fy[i] = mx[i] = my[i] = 0;
        FOR(j,1,N) c[i][j] = inf;
    }
}

void addEdge(int i, int j, long long cost) {
    c[i][j] = min(c[i][j], cost);
}

inline long long getC(int i, int j) {
    return c[i][j] - fx[i] - fy[j];
}

void initBFS() {
    front = rear = 1;
    qu[1] = start;
    memset(trace, 0, sizeof trace);
    FOR(j,1,N) {
        d[j] = getC(start, j);
        arg[j] = start;
    }
    finish = 0;
}

void findAugPath() {
    while (front <= rear) {
        int i = qu[front++];
        FOR(j,1,N) if (!trace[j]) {
            long long w = getC(i, j);
            if (!w) {
                trace[j] = i;
                if (!my[j]) {
                    finish = j;
                    return ;
                }
                qu[++rear] = my[j];
            }
            if (d[j] > w) {
                d[j] = w;
                arg[j] = i;
            }
        }
    }
}

void subx_addy() {
    long long delta = inf;
    FOR(j,1,N)
        if (trace[j] == 0 && d[j] < delta) delta = d[j];

    // xoay
    fx[start] += delta;
    FOR(j,1,N)
        if (trace[j]) {
            int i = my[j];
            fy[j] -= delta;
            fx[i] += delta;
        }
        else d[j] -= delta;

    FOR(j,1,N)
        if (!trace[j] && !d[j]) {
            trace[j] = arg[j];
            if (!my[j]) { finish = j; return ; }
            qu[++rear] = my[j];
        }
}

void enlarge() {
    do {
        int i = trace[finish];
        int next = mx[i];
        mx[i] = finish;
        my[finish] = i;
        finish = next;
    } while (finish);
}

int mincost() {
    FOR(i,1,N) fx[i] = *min_element(c[i]+1, c[i]+N+1);
    FOR(i,1,N) {
        start = i;
        initBFS();
        while (finish == 0) {
            findAugPath();
            if (!finish) subx_addy();
        }
        enlarge();
    }
    int res = 0;
    FOR(i,1,N) res += c[i][mx[i]];
    return res;
}

int n, k, p, cost[1011][33];
vector<int> ke[1011];
int f[1011][33][33];

void dfs(int u, int fu) {
    int children = 0;
    for(auto v : ke[u]) {
        if (v == fu) continue;
        dfs(v, u);
        ++children;
    }

    // can use same color for neighbours(u)
    FOR(cu,1,k) FOR(cf,1,k) {
        f[u][cu][cf] = p + cost[u][cu];

        for(int v : ke[u]) {
            if (v == fu) continue;

            int cur = inf;
            FOR(cv,1,k) cur = min(cur, f[v][cv][cu]);
            f[u][cu][cf] += cur;
        }
    }

    // cannot use same color
    int nColor = k;
    if (fu != -1) nColor--;

    if (children <= nColor) {
        FOR(cu,1,k) FOR(cf,1,k) {
            // init cost matrix
            N = max(children, nColor);
            init();
            FOR(i,children+1,N) FOR(j,1,k)
                addEdge(i, j, 0);
            int row = 0;
            for(int v : ke[u]) {
                if (v == fu) continue;
                ++row;
                int col = 0;
                FOR(color,1,k) {
                    if (color != cf || fu == -1) {
                        ++col;
                        addEdge(row, col, f[v][color][cu]);
                    }
                }
            }
            // 
            f[u][cu][cf] = min(f[u][cu][cf], cost[u][cu] + mincost());
        }
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cerr << "test = " << test << '/' << ntest << "...";
        cin >> n >> k >> p;
        FOR(i,1,n) FOR(j,1,k) cin >> cost[i][j];
        FOR(i,1,n) ke[i].clear();

        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        dfs(1, -1);

        int res = inf;
        FOR(cu,1,k) FOR(cf,1,k) res = min(res, f[1][cu][cf]);
        cout << "Case #" << test << ": " << res << endl;

        cerr << "DONE" << endl;
    }
}
