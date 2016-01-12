
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

int M, N, K;

struct Point {
    int x, y;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    int sum() { return x + y; }
    int diff() { return x - y; }

    friend istream& operator >> (istream& cin, Point& p) {
        cin >> p.x >> p.y;
        p.x *= 2;
        p.y *= 2;
        return cin;
    }
    friend ostream& operator << (ostream& cout, Point& p) {
        cout << p.x << ' ' << p.y;
        return cout;
    }

    void rotx() { x = M - x; }
    void roty() { y = N - y; }
    void rotr() { swap(x, y); }
};

struct Seg {
    Point A, B;

    Seg() {}
    Seg(Point A, Point B) : A(A), B(B) {}

    friend istream& operator >> (istream& cin, Seg& s) {
        cin >> s.A >> s.B;
        return cin;
    }
    friend ostream& operator << (ostream& cout, Seg& s) {
        cout << '(' << s.A << ") - (" << s.B << ")";
        return cout;
    }

    void rotx() { A.rotx(); B.rotx(); }
    void roty() { A.roty(); B.roty(); }
    void rotr() { A.rotr(); B.rotr(); }

    bool isHor() { return A.y == B.y; }
    bool isVer() { return A.x == B.x; }
    bool isSum() { return A.sum() == B.sum(); }
    bool isDiff(){ return A.diff() == B.diff(); }
} segs[333];

int hor[333], ver[333], sum[333], diff[333];
int nHor, nVer, nSum, nDiff;

void init() {
    nHor = nVer = nSum = nDiff = 0;
    FOR(i,1,K) {
        if (segs[i].isHor()) hor[++nHor] = segs[i].A.y;
        if (segs[i].isVer()) ver[++nVer] = segs[i].A.x;
        if (segs[i].isSum()) sum[++nSum] = segs[i].A.sum();
        if (segs[i].isDiff()) diff[++nDiff] = segs[i].A.diff();
    }
    assert(nHor + nVer + nSum + nDiff == K);
}

int solve1() {
    const int INF = 1e6;

    int res = 0;
    FOR(i,1,nVer) FOR(j,1,nHor) {
        int x = ver[i], y = hor[j];
        // Dem so tam giac co dinh goc vuong o (x, y) va 2 dinh con lai nam trong hcn (0,0) - (x,y)

        int min_side = INF;
        FOR(k,1,nSum) {
            int s = sum[k];
            int yy = s - x;
            int xx = s - y;

            if (xx < 0 || xx >= x) continue;
            if (yy < 0 || yy >= y) continue;

            assert(x - xx == y - yy);

            min_side = min(min_side, x - xx);
        }

        if (min_side == INF) continue;

        int min_bad = INF;
        FOR(k,1,nHor) {
            if (hor[k] < y) min_bad = min(min_bad, y - hor[k]);
        }
        FOR(k,1,nVer) {
            if (ver[k] < x) min_bad = min(min_bad, x - ver[k]);
        }
        FOR(k,1,nDiff) {
            int d = diff[k];
            int yy = x - d;
            if (yy >= 0 && yy <= y) min_bad = min(min_bad, y - yy);

            int xx = y + d;
            if (xx >= 0 && xx <= x) min_bad = min(min_bad, x - xx);
        }

        if (min_bad >= min_side) {
            ++res;
//            cout << "x = " << x << ", y = " << y << "    side = " << min_side << endl;
        }
    }
    return res;
}

int solve2() {
    const int INF = 1e6;

    int res = 0;
    FOR(i,1,nSum) FOR(j,1,nDiff) {
        int x = (sum[i] + diff[j]) / 2;
        int y = (sum[i] - diff[j]) / 2;

        if (x < 0 || x > M || y < 0 || y > N) continue;

        int min_side = INF;
        FOR(k,1,nHor) {
            if (hor[k] < y) min_side = min(min_side, y - hor[k]);
        }
        if (min_side == INF) continue;

        int min_bad = INF;
        FOR(k,1,nVer) {
            min_bad = min(min_bad, abs(x - ver[k]));
        }
        FOR(k,1,nSum) {
            int xx = (sum[k] + diff[j]) / 2;
            int yy = (sum[k] - diff[j]) / 2;

            if (yy < y) min_bad = min(min_bad, y - yy);
        }
        FOR(k,1,nDiff) {
            int xx = (sum[i] + diff[k]) / 2;
            int yy = (sum[i] - diff[k]) / 2;

            if (yy < y) min_bad = min(min_bad, y - yy);
        }

        if (min_bad >= min_side) {
//            cout << "x = " << x << ", y = " << y << "     " << min_side << endl;
            ++res;
        }
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("inlay.in", "r", stdin);
    freopen("inlay.out", "w", stdout);
    while (cin >> M >> N >> K) {
        M *= 2;
        N *= 2;

        FOR(i,1,K) cin >> segs[i];
        segs[++K] = Seg(Point(0, 0), Point(M, 0));
        segs[++K] = Seg(Point(0, N), Point(M, N));

        segs[++K] = Seg(Point(0, 0), Point(0, N));
        segs[++K] = Seg(Point(M, 0), Point(M, N));

        int res = 0;
        REP(rotx,2) {
            REP(roty,2) {
                init();
                res += solve1();
                if (rotx == 0) res += solve2();
                FOR(i,1,K) segs[i].roty();
            }
            FOR(i,1,K) segs[i].rotx();
        }

        swap(M, N);

        FOR(i,1,K) segs[i].rotr();

        init();

        res += solve2();
        FOR(i,1,K) segs[i].roty();

        init();
        res += solve2();
        cout << res << endl;
    }
}
