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

const int MN = 111;
struct Point {
    int x, y, id;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }

    friend ostream& operator << (ostream& cout, Point& p) {
        cout << p.x << ' ' << p.y;
        return cout;
    }
} a[MN];

int ccw(Point a, Point b, Point c) {
    b = b - a;
    c = c - a;
    int t = b.x * c.y - b.y * c.x;
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}

bool operator < (const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

int UP = ccw(Point(0, 0), Point(1, 0), Point(1, 1));
int DOWN = ccw(Point(0, 0), Point(1, 0), Point(1, -1));

struct Edge {
    int up, down;
    bool can;
} toFirst[MN], toLast[MN], c[MN][MN];
int n;
int visited[MN][MN][MN];
int tri[MN][MN][MN], tru[MN][MN][MN], trd[MN][MN][MN];

void init() {
    FOR(i,1,n) {
        toFirst[i].can = true;
        toFirst[i].up = toFirst[i].down = 0;

        FOR(j,1,n) if (j != i && a[j].x <= a[i].x && a[j].y == a[i].y) {
            toFirst[i].can = false;
            break;
        }

        FOR(j,1,i-1) {
            if (a[j].y == a[i].y) {
                toFirst[i].can = false;
                break;
            }
            else {
                if (a[j].y > a[i].y) ++toFirst[i].up;
                else ++toFirst[i].down;
            }
        }
    }

    FOR(i,1,n) {
        toLast[i].can = true;
        toLast[i].up = toLast[i].down = 0;

        FOR(j,1,n) if (j != i && a[j].x >= a[i].x && a[j].y == a[i].y) {
            toLast[i].can = false;
            break;
        }

        FOR(j,i+1,n) {
            if (a[i].y == a[j].y) {
                toLast[i].can = false;
            }
            else {
                if (a[j].y > a[i].y) ++toLast[i].up;
                else ++toLast[i].down;
            }
        }
    }

    FOR(i,1,n) FOR(j,i+1,n) {
        c[i][j].can = true;

        if (a[i].x == a[j].x) {
            c[i][j].can = false;
            continue;
        }

        FOR(k,i+1,j-1) if (ccw(a[i], a[k], a[j]) == 0) {
            c[i][j].can = false;
            break;
        }

        if (!c[i][j].can) continue;

        c[i][j].up = c[i][j].down = 0;
        FOR(k,i+1,j-1) {
            if (ccw(a[i], a[j], a[k]) == UP) ++c[i][j].up;
            else ++c[i][j].down;
        }
    }
    return ;

    cout << "toFirst" << endl;
    FOR(i,1,n) {
        cout << a[i].id << ": ";
        if (toFirst[i].can) cout << toFirst[i].up << ' ' << toFirst[i].down << endl;
        else cout << '-' << endl;
    }

    cout << "toLast" << endl;
    FOR(i,1,n) {
        cout << a[i].id << ": ";
        if (toLast[i].can) cout << toLast[i].up << ' ' << toLast[i].down << endl;
        else cout << '-' << endl;
    }

    DEBUG(c[1][4].up);
    DEBUG(c[1][4].down);
}

int max3(int a, int b, int c) {
    return max(max(a, b), c);
}
int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

vector<int> res;
void trace(int i, int u, int d) {
    if (i == 0) return ;
    trace(tri[i][u][d], tru[i][u][d], trd[i][u][d]);

    res.push_back(a[i].id);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("division.in", "r", stdin);
    freopen("division.out", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].x >> a[i].y;
            a[i].id = i;
        }
        sort(a+1, a+n+1);
        init();

        memset(visited, 0, sizeof visited);
        queue<int> qi, qup, qdown;
        FOR(i,1,n) if (toFirst[i].can) {
            int up = toFirst[i].up;
            int down = toFirst[i].down;

            qi.push(i);
            qup.push(up);
            qdown.push(down);

            visited[i][up][down] = 1;
            tri[i][up][down] = 0;
            tru[i][up][down] = 0;
            trd[i][up][down] = 0;
        }
        while (!qi.empty()) {
            int i = qi.front(); qi.pop();
            int up = qup.front(); qup.pop();
            int down = qdown.front(); qdown.pop();

            FOR(j,i+1,n) if (c[i][j].can) {
                int i2 = j;
                int up2 = up + c[i][j].up;
                int down2 = down + c[i][j].down;

                if (!visited[i2][up2][down2]) {
                    qi.push(i2);
                    qup.push(up2);
                    qdown.push(down2);
                    visited[i2][up2][down2] = 1;

                    tri[i2][up2][down2] = i;
                    tru[i2][up2][down2] = up;
                    trd[i2][up2][down2] = down;
                }
            }
        }

        int best = 1e9;
        int savei = -1;
        int saveu = -1;
        int saved = -1;
        FOR(i,1,n) FOR(up,0,i) FOR(down,0,i)
            if (visited[i][up][down] && toLast[i].can) {
                int u = up + toLast[i].up;
                int d = down + toLast[i].down;
                int m = n - u - d;

                int cur = max3(u, d, m) - min3(u, d, m);
                if (cur < best) {
                    best = cur;
                    savei = i;
                    saveu = up;
                    saved = down;
                }
            }

//        DEBUG(best);

        res.clear();
        trace(savei, saveu, saved);
        cout << SZ(res) << '\n';
        for(int x : res) cout << x << ' '; cout << endl;
    }
}
