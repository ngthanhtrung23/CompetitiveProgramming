
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

int visited[1000111];

void solve(int a, int b) {
    int cur = 0;
    while (true) {
        if (a == 0) {
            cout << cur << ' ' << 0 << endl;
            return ;
        }
        if (visited[a]) {
            cout << visited[a]-1 << ' ' << cur - visited[a] + 1 << endl;
            return ;
        }
        visited[a] = ++cur;
        a = (a * 10) % b;
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);

    int a, b;
    while (cin >> a >> b) {
        a %= b;
        memset(visited, 0, sizeof visited);

        solve(a, b);
    }
}
