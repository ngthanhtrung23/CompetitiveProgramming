#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cassert>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
// On CF, GNU C++ seems to have some precision issues with long double?
// #define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define stat akjcjalsjcjalscj
#define hash ajkscjlsjclajsc
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (((S) >> (X)) & 1)

long long rand16() {
    return rand() & (TWO(16) - 1);
}
long long my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(long long& x) { return scanf("%lld", &x); }

const int MN = 400111;

struct Position {
    int r, c;
    Position(int r, int c) : r(r), c(c) {}
};

bool operator < (const Position& a, const Position& b) {
    if (a.r != b.r) return a.r < b.r;
    return a.c < b.c;
}

int nId, nRow, nCol, nPos;
map<Position, int> posId;
set<int> rows[MN], cols[MN];
vector<int> adj[MN];
int inDeg[MN];

void init() {
    posId.clear();
    nId = 0;

    FOR(i,1,nRow) rows[i].clear();
    FOR(j,1,nCol) cols[j].clear();
    FOR(i,1,nPos) adj[i].clear();
    memset(inDeg, 0, sizeof inDeg);
}

const int di[4] = {-1, 1, 0, 0};
const int dj[4] = {0, 0, -1, 1};
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

void addEdge(int u, int v) {
    adj[u].push_back(v);
    inDeg[v]++;
}

bool visited[MN];
pair<char, int> how[MN];

void dfs1(int r, int c, int prevDir) {
    int u = posId[Position(r, c)];
    visited[u] = true;

    if (prevDir == DOWN) {
        auto it = cols[c].upper_bound(r);
        if (it != cols[c].end()) {
            int r2 = *it;

            int v = posId[Position(r2, c)];
            assert(u != v);
            addEdge(u, v);
        }

        how[u] = make_pair('^', c);
    }
    if (prevDir == UP) {
        auto it = cols[c].lower_bound(r);
        if (it != cols[c].begin()) {
            --it;
            int r2 = *it;
            int v = posId[Position(r2, c)];
            assert(u != v);
            addEdge(u, v);
        }

        how[u] = make_pair('v', c);
    }
    if (prevDir == RIGHT) {
        auto it = rows[r].upper_bound(c);
        if (it != rows[r].end()) {
            int c2 = *it;
            int v = posId[Position(r, c2)];
            assert(u != v);
            addEdge(u, v);
        }

        how[u] = make_pair('<', r);
    }
    if (prevDir == LEFT) {
        auto it = rows[r].lower_bound(c);
        if (it != rows[r].begin()) {
            --it;
            int c2 = *it;
            int v = posId[Position(r, c2)];
            assert(u != v);
            addEdge(u, v);
        }

        how[u] = make_pair('>', r);
    }

    REP(dir,4) if (dir != (prevDir ^ 1)) {
        int r2 = r + di[dir];
        int c2 = c + dj[dir];
        Position p(r2, c2);
        if (posId.count(p)) {
            int v = posId[p];
            if (!visited[v]) {
                addEdge(u, v);
                dfs1(r2, c2, dir);
            }
        }
    }
}

vector<int> all;
bool noCycle() {
    stack<int> st;
    FOR(i,1,nPos) {
        if (inDeg[i] == 0) {
            st.push(i);
        }
    }
    int cnt = 0;
    while (!st.empty()) {
        ++cnt;
        int u = st.top(); st.pop();
        all.push_back(u);

        for (int v : adj[u]) {
            --inDeg[v];
            if (inDeg[v] == 0) st.push(v);
        }
    }
    if (cnt == nPos) {
        FOR(i,1,nPos) assert(inDeg[i] == 0);
    }

    return cnt == nPos;
}

set< pair<int,int> > points;
set< pair<int,int> > actual;
set<int> actual_rows[MN], actual_cols[MN];

bool verify() {
    for (auto u : all) {
        if (u == 1) {
            continue;
        }
        int r, c;
        if (how[u].first == '<') {
            r = how[u].second;
            if (actual_rows[r].empty()) return false;
            c = *actual_rows[r].rbegin(); ++c;
        } else if (how[u].first == '>') {
            r = how[u].second;
            if (actual_rows[r].empty()) return false;
            c = *actual_rows[r].begin(); --c;
        } else if (how[u].first == '^') {
            c = how[u].second;
            if (actual_cols[c].empty()) return false;
            r = *actual_cols[c].rbegin(); ++r;
        } else if (how[u].first == 'v') {
            c = how[u].second;
            if (actual_cols[c].empty()) return false;
            r = *actual_cols[c].begin(); --r;
        }
        actual.insert({r, c});
        actual_rows[r].insert(c);
        actual_cols[c].insert(r);
    }
    return actual == points;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (cin >> nRow >> nCol >> nPos) {
        init();
        int startRow = -1, startCol = -1;
        points.clear();
        actual.clear();
        FOR(i,1,nRow) actual_rows[i].clear();
        FOR(j,1,nCol) actual_cols[j].clear();

        FOR(i,1,nPos) {
            int r, c; cin >> r >> c;
            if (i == 1) {
                startRow = r;
                startCol = c;
            }

            Position p(r, c);
            assert(!posId.count(p));

            posId[p] = i;
            rows[r].insert(c);
            cols[c].insert(r);

            points.insert({r, c});
            if (i == 1) {
                actual.insert({r, c});
                actual_rows[r].insert(c);
                actual_cols[c].insert(r);
            }
        }
        memset(visited, 0, sizeof visited);
        dfs1(startRow, startCol, -1);

        all.clear();
        if (!noCycle() || !verify()) {
            cout << "impossible" << endl;
        } else {
            cout << "possible" << endl;
            for (auto u : all) {
                if (u == 1) continue;
                cout << how[u].first << ' ' << how[u].second << '\n';
            }
        }
    }
    return 0;
}
