#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cout << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cout << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cout << A[_] << ' '; cout << endl; }
#define PR0(A, n) { cout << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cout << A[_] << ' '; cout << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

struct Point {
    int x, y;

    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
};

ostream& operator << (ostream& cout, const Point& p) {
    cout << '(' << p.x << ' ' << p.y << ')';
    return cout;
}

Point operator - (const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

string board[55];
int regionId[55][55];
int nRow, nCol;

struct Region {
    char c;
    int id;
    Point top;
    vector<Point> offsets;

    void clearFromBoard() {
        for (auto offset : offsets) {
            int x = top.x + offset.x;
            int y = top.y + offset.y;

            assert(board[x][y] == c);
            board[x][y] = '.';
            regionId[x][y] = -1;
        }
    }
};
bool visited[55][55];

const int dirs[5] = {-1, 0, 1, 0, -1};
const string dirc = "DL_R";

bool inside(int r, int c) {
    return 0 <= r && r < nRow
        && 0 <= c && c < nCol;
}

bool canMove(const Region& region, int r, int c) {
    for (auto offset : region.offsets) {
        int r2 = r + offset.x;
        int c2 = c + offset.y;

        if (!inside(r2, c2)) return false;
        if (regionId[r2][c2] != -1 && regionId[r2][c2] != region.id) {
            return false;
        }
    }
    return true;
}

pair<int,int> tr[55][55];
char trc[55][55];

pair<int, string> findPath(const Region& region, const Point& start) {
    int r = start.x, c = start.y;
    pair<int,string> res = {start.y + 1, ""};

    while (r != region.top.x || c != region.top.y) {
        res.second += trc[r][c];

        auto [r2, c2] = tr[r][c];
        r = r2;
        c = c2;
    }
    res.second += 'S';

    // cout << "Deleting: " << region.c << endl;
    // cout << res.first << ' ' << res.second << endl;

    return res;
}

bool canClear(const Region& region, pair<int, string> &trace) {
    memset(tr, -1, sizeof tr);

    queue<Point> qu;
    qu.push(region.top);

    while (!qu.empty()) {
        auto top = qu.front(); qu.pop();

        if (top.x == 0) {
            trace = findPath(region, top);
            return true;
        }

        REP(dir,4)
        if (dir != 2) {  // cannot move up (-1, 0)
            int r = top.x + dirs[dir];
            int c = top.y + dirs[dir + 1];

            if (tr[r][c].first < 0 && canMove(region, r, c)) {
                tr[r][c] = {top.x, top.y};
                trc[r][c] = dirc[dir];
                qu.push(Point(r, c));
            }
        }
    }

    return false;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (cin >> nRow >> nCol) {
        REP(i,nRow) cin >> board[i];

        // init regions
        vector<Region> regions;
        memset(visited, 0, sizeof visited);
        memset(regionId, -1, sizeof regionId);

        int nRegion = 0;

        REP(i,nRow) REP(j,nCol) {
            if (!visited[i][j] && board[i][j] != '.') {
                Region region;
                region.id = ++nRegion;
                region.c = board[i][j];
                region.top = Point(i, j);
                region.offsets.push_back({0, 0});
                visited[i][j] = true;
                regionId[i][j] = nRegion;

                queue< pair<int,int> > qu;
                qu.push({i, j});
                while (!qu.empty()) {
                    auto [r, c] = qu.front(); qu.pop();

                    REP(dir,4) {
                        int r2 = r + dirs[dir];
                        int c2 = c + dirs[dir + 1];
                        if (!inside(r2, c2) || visited[r2][c2]) continue;
                        if (board[r][c] != board[r2][c2]) continue;

                        visited[r2][c2] = true;
                        regionId[r2][c2] = nRegion;
                        qu.push({r2, c2});
                        region.offsets.push_back({r2 - i, c2 - j});
                    }
                }

                regions.push_back(region);
            }
        }

        /*
        for (auto region : regions) {
            cout << region.c << ": " << region.top << endl;
            cout << "   ";
            for (auto offset : region.offsets) cout << offset << "  ";
            cout << endl;
        }
        REP(i,nRow) PR0(regionId[i], nCol);
        */

        //
        try {
            vector< pair<int, string> > res;

            REP(turn,SZ(regions)) {
                // cout << "------" << endl;
                // REP(i,nRow) cout << board[i] << endl;

                bool ok = false;
                REP(r,SZ(regions)) {
                    auto region = regions[r];
                    pair<int, string> trace = {-1, ""};
                    if (canClear(region, trace)) {
                        ok = true;
                        region.clearFromBoard();
                        res.push_back(trace);
                        regions.erase(regions.begin() + r);
                        break;
                    }
                }
                if (!ok) throw 1;
            }

            reverse(ALL(res));
            cout << SZ(res) << '\n';
            for (auto p : res) cout << p.first << ' ' << p.second << "\n";
        } catch (...) {
            cout << -1 << endl;
        }
        cout << endl;
    }
    return 0;
}
