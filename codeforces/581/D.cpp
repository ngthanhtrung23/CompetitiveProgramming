
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

int x[3], y[3];
int n;
char a[333][333];
bool used[3];

bool empty(int i1, int i2, int j1, int j2) {
    FOR(i,i1,i2) FOR(j,j1,j2)
        if (a[i][j] != ' ') return false;
    return true;
}

void attempt(int i, int j) {
    if (i == n+1) throw 1;

    int ii = i, jj = j + 1;
    if (jj > n) {
        jj = 1;
        ++ii;
    }

    if (a[i][j] != ' ') {
        attempt(ii, jj);
        return ;
    }

    REP(t,3) if (!used[t]) {
        int u = x[t], v = y[t];
        REP(rot,2) {
            if (i + u - 1 <= n && j + v - 1 <= n && empty(i, i+u-1, j, j+v-1)) {
                FOR(ii,i,i+u-1) FOR(jj,j,j+v-1)
                    a[ii][jj] = 'A' + t;

                used[t] = 1;
                attempt(ii, jj);
                used[t] = 0;

                FOR(ii,i,i+u-1) FOR(jj,j,j+v-1)
                    a[ii][jj] = ' ';
            }

            swap(u, v);
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2]) {
        int sum = 0;
        REP(i,3) sum += x[i] * y[i];
        n = (int) (sqrt(sum) + 1e-3);

        memset(used, 0, sizeof used);
        
        if (n*n != sum) {
            cout << -1 << endl;
            continue;
        }
        try {
            memset(a, ' ', sizeof a);
            attempt(1, 1);
            cout << -1 << endl;
        } catch (...) {
            cout << n << endl;
            FOR(i,1,n) {
                FOR(j,1,n) cout << a[i][j];
                cout << endl;
            }
        }
    }
}

