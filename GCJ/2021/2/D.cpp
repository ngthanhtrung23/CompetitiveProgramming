#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

string a[22], b[22];

class Matching {
public:
    Matching(int n = 0) {
        N = n;
        cost = VII(n, VI(n, INF));
        adj = VII(n);

        trace = VI(n);
        arg = VI(n);
        fx = VI(n, -INF);
        fy = VI(n);
        d = VI(n);
        mx = VI(n, -1);
        my = VI(n, -1);
    }

    void AddEdge(int x, int y, int c) {
        if (cost[x][y] == INF) adj[x].push_back(y);
        if (cost[x][y] > c) cost[x][y] = c;
    }

    int GetMinCost() {
        for (int x = 0; x < N; x++) {
            initBFS(x);
            int finish = -1;
            do {                
                finish = findPath();
                if (finish != -1) break;
                finish = update(x);
            } while (finish == -1);
            enlarge(finish);
        }
        int ret = 0;
        for (int x = 0; x < N; x++) 
            ret += cost[x][mx[x]];
        return ret;
    }

private:
    typedef vector<int> VI;
    typedef vector<VI> VII;
    const int INF = 1e9;

    int N;
    VII cost, adj;
    VI d, fx, fy, mx, my, arg, trace;

    queue<int> q;

    int getCost(int x, int y) {
        return cost[x][y] - fx[x] - fy[y];
    }

    void initBFS(int start) {
        for (int i = 0; i < N; i++)
            trace[i] = -1;
        while (!q.empty()) q.pop();
        q.push(start);
        for (int i = 0; i < N; i++)
            d[i] = getCost(start, i), arg[i] = start;
    }

    int findPath() {
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int i = 0; i < (int) adj[x].size(); i++) {
                int y = adj[x][i];
                if (trace[y] == -1) {
                    int w = getCost(x, y);
                    if (w == 0) {
                        trace[y] = x;
                        if (my[y] == -1) 
                            return y;
                        q.push(my[y]);
                    }
                    if (d[y] > w) {
                        d[y] = w;
                        arg[y] = x;
                    }
                }
            }
        }
        return -1;
    }

    int update(int start) {
        int delta = INF;
        for (int y = 0; y < N; y++)
            if (trace[y] == -1)
                delta = min(delta, d[y]);   
        fx[start] += delta;
        for (int y = 0; y < N; y++)
            if (trace[y] != -1) {
                int x = my[y];
                fx[x] += delta;
                fy[y] -= delta;
            } 
            else d[y] -= delta;
        for (int y = 0; y < N; y++)
            if (trace[y] == -1 && d[y] == 0) {
                trace[y] = arg[y];
                if (my[y] == -1) 
                    return y;
                q.push(my[y]);
            }
        return -1;
    }

    void enlarge(int finish) {
        for (int y = finish; y != -1; ) {
            int x = trace[y];
            int yy = mx[x];
            mx[x] = y;
            my[y] = x;
            y = yy;
        }
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int nRow, nCol, flipCost, swapCost;
        auto id = [&] (int i, int j) {
            return (i - 1) * nCol + j;
        };
        cin >> nRow >> nCol >> flipCost >> swapCost;
        FOR(i,1,nRow) {
            cin >> a[i];
            a[i] = " " + a[i] + " ";
        }
        FOR(i,1,nRow) {
            cin >> b[i];
            b[i] = " " + b[i] + " ";
        }
        int flip = 0;
        FOR(i,1,nRow) FOR(j,1,nCol) {
            if (a[i][j] != b[i][j]) ++flip;
        }

        Matching match(nRow * nCol);
        FOR(i,1,nRow) FOR(j,1,nCol) {
            int u = id(i, j) - 1;

            if (a[i][j] == b[i][j]) match.AddEdge(u, u, 0);
            else match.AddEdge(u, u, 2 * flipCost);

            FOR(ii,1,nRow) FOR(jj,1,nCol) {
                int dist = abs(ii - i) + abs(jj - j);

                int v = id(ii, jj) - 1;
                if (a[i][j] == b[ii][jj]
                        && a[ii][jj] == b[i][j]) {
                    match.AddEdge(u, v, dist * swapCost);
                }
            }
        }
        int res = match.GetMinCost() / 2;

        cout << "Case #" << test << ": " << res << endl;
    }
    return 0;
}
