
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

const int MN = 211;

struct Point {
    ll x, y;
    int id;

    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}

    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    ll operator % (const Point& a) const { return x*a.y - y*a.x; }
    ll sqlen() { return x*x + y*y; }

    friend istream& operator >> (istream& cin, Point& p) {
        cin >> p.x >> p.y;
        return cin;
    }
    friend ostream& operator << (ostream& cout, Point& p) {
        cout << p.x << ' ' << p.y;
        return cout;
    }
} reds[MN], blues[MN];

bool operator < (const Point& a, const Point& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

int ccw(const Point& a, const Point& b, const Point& c) {
    ll t = (b - a) % (c - a);
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}

ll area2(const Point& a, const Point& b, const Point& c) {
    return llabs((b - a) % (c - a));
}

int nRed, nBlue;
vector<int> res;

pair<Point,int> a[MN];
ll f[MN][MN];
int tr[MN][MN];
ll can[MN][MN];

struct Comp {
    Point root;

    bool operator() (const pair<Point,int>& a, const pair<Point,int>& b) {
        int t = ccw(root, a.first, b.first);
        if (t == 0) {
            return (a.first - root).sqlen() > (b.first- root).sqlen();
        }
        return t > 0;
    }
} cmp;

ll best;
void trace(int i, int j) {
    if (tr[i][j] == 0) {
        auto p = a[i].first; res.push_back(p.id);
        auto q = a[j].first; res.push_back(q.id);
    }
    else {
        trace(tr[i][j], i);
        auto p = a[j].first; res.push_back(p.id);
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> nRed) {
        FOR(i,1,nRed) {
            cin >> reds[i];
            reds[i].id = i;
        }
        cin >> nBlue;
        FOR(i,1,nBlue) cin >> blues[i];

        best = 0;
        res.clear();
        FOR(root,1,nRed) {
            int k = 0;
            FOR(i,1,nBlue) if (reds[root] < blues[i]) {
                a[++k] = make_pair(blues[i], -1);
            }
            int savek = k;
            FOR(i,1,nRed) if (reds[root] < reds[i]) {
                bool ok = true;
                FOR(j,1,savek) {
                    if (ccw(reds[root], a[j].first, reds[i]) == 0) {
                        ll l1 = (a[j].first - reds[root]).sqlen();
                        ll l2 = (reds[i] - reds[root]).sqlen();
                        if (l1 <= l2) {
                            ok = false;
                            break;
                        }
                    }
                }
                if (ok)
                    a[++k] = make_pair(reds[i], +1);
            }
            Comp cmp;
            cmp.root = reds[root];
            sort(a+1, a+k+1, cmp);

            FOR(i,1,k) FOR(j,1,k) f[i][j] = tr[i][j] = 0;
            memset(can, 0, sizeof can);
            FOR(i,1,k) {
                if (a[i].second == -1) continue;

                bool hasLower = false;
                Point minBlue = Point(0, 0);
                FOR(j,i+1,k) {
                    if (a[j].second == -1) {
                        if (!hasLower) {
                            hasLower = true;
                            minBlue = a[j].first;
                        }
                        else {
                            if (ccw(a[i].first, minBlue, a[j].first) == 1) {
                                minBlue = a[j].first;
                            }
                        }
                    }
                    else {
                        if (hasLower
                                && ccw(a[i].first, minBlue, a[j].first) != 1) continue;
                        can[i][j] = area2(reds[root], a[i].first, a[j].first);
                    }
                }
            }
            FOR(i,1,k) FOR(j,i+1,k)
                if (can[i][j]) {
                    f[i][j] = can[i][j];
                }

            FOR(i,1,k) FOR(j,i+1,k) if (f[i][j]) {
                FOR(x,j+1,k) if (can[j][x] && ccw(a[i].first, a[j].first, a[x].first) == 1) {
                    if (f[j][x] < f[i][j] + can[j][x]) {
                        f[j][x] = f[i][j] + can[j][x];
                        tr[j][x] = i;
                    }
                }
            }

            FOR(i,1,k) FOR(j,i,k) if (f[i][j] > best) {
                best = f[i][j];
                res.clear();
                trace(i, j);
                res.push_back(reds[root].id);
            }
        }
//        DEBUG(best);
        cout << SZ(res) << '\n';
        for(int x : res) cout << x << ' '; cout << endl;
    }
}
