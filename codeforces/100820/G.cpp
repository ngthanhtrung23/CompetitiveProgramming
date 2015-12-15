
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

const int MN = 100111;

struct Point {
    ll x, y;
    ll sum, diff;
} a[MN];

bool operator < (const Point& a, const Point& b) {
    return a.sum < b.sum;
}

int n, r;
ll W, H;
ll c[MN];
int sc;

void RR() {
    FOR(i,1,n) {
        c[i] = a[i].diff;
    }
    sort(c+1, c+n+1);
    sc = unique(c+1, c+n+1) - c - 1;

    FOR(i,1,n) a[i].diff = lower_bound(c+1, c+sc+1, a[i].diff) - c;
}

int bit[MN], f[MN];

int get(int u) {
    int res = 0;
    for(int x = u; x > 0; x -= x & -x)
        res = max(res, bit[x]);
    return res;
}
void update(int u, int val) {
    for(int x = u; x < MN; x += x & -x)
        bit[x] = max(bit[x], val);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> r >> W >> H) {
        FOR(i,1,n) {
            cin >> a[i].x >> a[i].y;
            a[i].x *= r;
            a[i].sum = a[i].x + a[i].y;
            a[i].diff = a[i].y - a[i].x;
        }
        sort(a+1, a+n+1);
        RR();

        memset(bit, 0, sizeof bit);

        FOR(i,1,n) {
            f[i] = 1 + get(a[i].diff);
            update(a[i].diff, f[i]);
        }
        cout << *max_element(f+1, f+n+1) << endl;
    }
}
