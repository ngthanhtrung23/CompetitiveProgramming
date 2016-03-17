
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 50111;

struct Point {
    int x, y;
    int id;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
} a[MN];
int f[MN], n, fLeft[MN], fRight[MN];
int tr[MN], trLeft[MN], trRight[MN];

bool operator < (const Point& a, const Point& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

map<int,pair<int,int> > up, sum, dif;

void init() {
    up.clear();
    sum.clear();
    dif.clear();
    memset(f, 0, sizeof f);
    f[1] = MN;
}

int max3(int a, int b, int c) {
    return max(max(a, b), c);
}

void update(int t) {
    int opt = max3(f[t], fLeft[t], fRight[t]);

    int x = a[t].x;
    int s = a[t].x + a[t].y;
    int d = a[t].x - a[t].y;

    up[x] = max(up[x], make_pair(opt, t));
    sum[s] = max(sum[s], make_pair(opt, t));
    dif[d] = max(dif[d], make_pair(opt, t));
}

void goLeft(int t);
void goRight(int t);

vector<int> res;

void goDown(int t) {
    if (t <= 1) return ;

    int prev = tr[t];

    if (f[prev] + 1 == f[t]) goDown(prev);
    else if (fLeft[prev] + 1 == f[t]) goLeft(prev);
    else goRight(prev);

    res.push_back(t);
}
void goLeft(int t) {
    if (t <= 1) return ;

    int prev = trLeft[t];
    goDown(prev);

    int x = prev;
    while (a[x-1].y == a[t].y) {
        --x;
        res.push_back(x);
    }

    FOR(x,prev+1,t) {
        res.push_back(x);
    }
}
void goRight(int t) {
    if (t <= 1) return ;

    int prev = trRight[t];
    goDown(prev);

    int x = prev;
    while (a[x+1].y == a[t].y) {
        ++x;
        res.push_back(x);
    }

    FORD(x,prev-1,t) {
        res.push_back(x);
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("queen.in", "r", stdin);
    freopen("queen.out", "w", stdout);
    while (cin >> n) {
        init();

        FOR(i,1,n) {
            cin >> a[i].x >> a[i].y;
            a[i].id = i;
        }
        a[++n] = Point(0, 0);
        sort(a+1, a+n+1);

        f[1] = MN;
        fLeft[1] = fRight[1] = MN;
        update(1);

        int i = 2;
        while (i <= n) {
            int u = i, v = i;
            while (v + 1 <= n && a[v+1].y == a[u].y) ++v;

            // calculate f[u --> v]
            FOR(t,u,v) {
                int x = a[t].x;
                int s = a[t].x + a[t].y;
                int d = a[t].x - a[t].y;

                if (up[x].first + 1 > f[t]) {
                    f[t] = up[x].first + 1;
                    tr[t] = up[x].second;
                }
                if (sum[s].first + 1 > f[t]) {
                    f[t] = sum[s].first + 1;
                    tr[t] = sum[s].second;
                }
                if (dif[d].first + 1 > f[t]) {
                    f[t] = dif[d].first + 1;
                    tr[t] = dif[d].second;
                }
            }

            int iMax = -1, fMax = -1;
            FOR(t,u,v) {
                if (iMax < 0) {
                    fLeft[t] = -1;
                    iMax = t;
                    fMax = f[t];
                }
                else {
                    fLeft[t] = fMax + (t - u);
                    trLeft[t] = iMax;
                    if (fMax < f[t]) {
                        fMax = f[t];
                        iMax = t;
                    }
                }
            }
            iMax = -1, fMax = -1;
            FORD(t,v,u) {
                if (iMax < 0) {
                    fRight[t] = -1;
                    iMax = t;
                    fMax = f[t];
                }
                else {
                    fRight[t] = fMax + (v - t);
                    trRight[t] = iMax;
                    if (fMax < f[t]) {
                        fMax = f[t];
                        iMax = t;
                    }
                }
            }

            FOR(t,u,v) update(t);

            i = v + 1;
        }

        int ln = 0;
        FOR(i,1,n) {
            ln = max(ln, f[i]);
            ln = max(ln, fLeft[i]);
            ln = max(ln, fRight[i]);
        }
        cout << ln - MN << endl;
        res.clear();
        FOR(i,1,n) {
            if (f[i] == ln) {
                goDown(i);
                break;
            }
            if (fLeft[i] == ln) {
                goLeft(i);
                break;
            }
            if (fRight[i] == ln) {
                goRight(i);
                break;
            }
        }
        for(int x : res) cout << a[x].id << ' ';
        cout << endl;
    }
}

