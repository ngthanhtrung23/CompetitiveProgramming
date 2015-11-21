#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;
int n, k;
pair<int,int> a[MN];
pair<int,int> allx[MN], ally[MN];
int inAllx[MN], inAlly[MN];
int minx, maxx, miny, maxy;
bool removed[MN];

pair<int,int> read() {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    return make_pair(x1 + x2, y1 + y2);
}

ll res;

void removeRect(int i) {
    removed[i] = true;
    while (removed[allx[minx].second]) ++minx;
    while (removed[allx[maxx].second]) --maxx;
    while (removed[ally[miny].second]) ++miny;
    while (removed[ally[maxy].second]) --maxy;
}

void addRect(int i) {
    removed[i] = false;
    minx = min(minx, inAllx[i]);
    miny = min(miny, inAlly[i]);

    maxx = max(maxx, inAllx[i]);
    maxy = max(maxy, inAlly[i]);
}

ll getArea() {
    ll dx = allx[maxx].first - allx[minx].first; if (dx < 1) dx = 1; if (dx % 2) ++dx;
    ll dy = ally[maxy].first - ally[miny].first; if (dy < 1) dy = 1; if (dy % 2) ++dy;
    return dx * dy;
}

void solve(int i) {
    if (i > k) {
        res = min(res, getArea());
        return ;
    }
    int u;
    u = allx[minx].second;
    removeRect(u); solve(i+1); addRect(u);

    u = allx[maxx].second;
    removeRect(u); solve(i+1); addRect(u);

    u = ally[miny].second;
    removeRect(u); solve(i+1); addRect(u);

    u = ally[maxy].second;
    removeRect(u); solve(i+1); addRect(u);
}

int main() {
    while (scanf("%d%d", &n, &k) == 2) {
        FOR(i,1,n) a[i] = read();

        FOR(i,1,n) allx[i] = make_pair(a[i].first, i);
        FOR(i,1,n) ally[i] = make_pair(a[i].second, i);
        sort(allx+1, allx+n+1);
        sort(ally+1, ally+n+1);

        FOR(i,1,n) {
            inAllx[allx[i].second] = i;
            inAlly[ally[i].second] = i;
        }

        memset(removed, 0, sizeof removed);
        minx = 1; maxx = n;
        miny = 1; maxy = n;

        res = getArea();
        solve(1);
        cout << res / 4 << endl;
    }
}
