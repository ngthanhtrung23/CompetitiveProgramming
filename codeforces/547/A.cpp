#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

#define y1 y1__
#define next next__
long long m, h[2], x[2], y[2], a[2];

int visited[1000111];

long long next(long long h, int turn) {
    return (h * x[turn] + y[turn]) % m;
}
int get(long long from, long long to, int turn) {
    memset(visited, 0, sizeof visited);

    FOR(res,1,1000111) {
        from = next(from, turn);
        if (from == to) return res;

        if (visited[from]) return -1;
        visited[from] = res;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m) {
        REP(turn,2) {
            cin >> h[turn] >> a[turn] >> x[turn] >> y[turn];
        }

        long long tail[2], cycle[2];

        REP(turn,2) {
            tail[turn] = get(h[turn], a[turn], turn);
            cycle[turn] = get(a[turn], a[turn], turn);
        }
//        PR0(tail, 2);
//        PR0(cycle, 2);

        if (tail[0] < 0 || tail[1] < 0) cout << -1 << endl;
        else {
            if (tail[0] == tail[1]) cout << tail[0] << endl;
            else if (cycle[0] < 0 && cycle[1] < 0) cout << -1 << endl;
            else if (cycle[0] < 0) {
                int x = tail[0] - tail[1];
                if (x >= 0 && x % cycle[1] == 0) cout << tail[0] << endl;
                else cout << -1 << endl;
            }
            else if (cycle[1] < 0) {
                int x = tail[1] - tail[0];
                if (x >= 0 && x % cycle[0] == 0) cout << tail[1] << endl;
                else cout << -1 << endl;
            }
            else {
                bool ok = false;
                FOR(k0,0,10001111) {
                    long long x = k0 * cycle[0] + tail[0] - tail[1];
                    if (x >= 0 && x % cycle[1] == 0) {
                        ok = true;
                        cout << k0 * cycle[0] + tail[0] << endl;
                        break;
                    }
                }
                if (!ok) cout << -1 << endl;
            }
        }
    }
    return 0;
}