#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 1011;
double x[MN], y[MN];
int r[MN];
pair<int,int> k[MN];
int dir[MN];
bool visited[MN];

const double EPS = 1e-6;
#define sqr(x) ((x) * (x))
bool good(int u, int v) {
    return fabs(r[u] + r[v] - sqrt(sqr(x[u] - x[v]) + sqr(y[u] - y[v]))) < EPS;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    while (ntest--) {
        k[0] = make_pair(1, 1);
        int n; cin >> n;
        FOR(i,1,n) cin >> x[i] >> y[i] >> r[i];

        queue<int> qu; qu.push(1);
        memset(visited, false, sizeof visited);
        visited[1] = true;
        dir[1] = 0;
        k[1] = make_pair(1, 1);
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            FOR(v,1,n) if (!visited[v] && good(u, v)) {
                visited[v] = true;
                dir[v] = dir[u] ^ 1;
                k[v] = make_pair(r[1], r[v]);
                qu.push(v);
            }
        }
        FOR(i,1,n) {
            if (visited[i]) {
                int g = __gcd(k[i].first, k[i].second);
                int x = k[i].first / g, y = k[i].second / g;
                if (y == 1) cout << x << ' ';
                else cout << x << '/' << y << ' ';
                if (dir[i]) cout << "counterclockwise";
                else cout << "clockwise";
                cout << endl;
            }
            else cout << "not moving" << endl;
        }
    }
    return 0;
}

