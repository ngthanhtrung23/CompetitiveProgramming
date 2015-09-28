
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 4011;

int x[MN], y[MN], to[MN];
int n;

bool intersect(int i, int j, int &cut_x, int& cut_y) {
    if (x[i-1] == x[i] && x[j-1] == x[j]) return false;
    if (y[i-1] == y[i] && y[j-1] == y[j]) return false;

    if (x[i-1] == x[i]) swap(i, j);

    if (max(x[i-1], x[i]) < x[j] || x[j] < min(x[i-1], x[i])) return false;
    if (max(y[j-1], y[j]) < y[i] || y[i] < min(y[j-1], y[j])) return false;

    cut_x = x[j];
    cut_y = y[i];
    return true;
}

int dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> x[i] >> y[i];
            if (i > 1) {
                to[i] = to[i-1] + dist(x[i], y[i], x[i-1], y[i-1]);
            }
        }
        int res = to[n];
//        DEBUG(res);
        
        FOR(i,2,n) {
            FOR(j,1,i-2) {
                int u, v;
                if (intersect(i, j, u, v)) {
                    int t1 = to[j-1] + dist(x[j-1], y[j-1], u, v);
                    int t2 = to[i-1] + dist(x[i-1], y[i-1], u, v);

                    res = min(res, t2 - t1);
                }
            }
        }
        cout << res << endl;
    }
}
