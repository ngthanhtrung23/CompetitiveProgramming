
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

char a[11][11], c[11][11];

void print(int m, int n) {
    FOR(i,1,m) {
        FOR(j,1,n) cout << a[i][j];
        cout << '\n';
    }
}

void rotate(int m, int n) {
    FOR(i,1,m) FOR(j,1,n) c[i][j] = a[i][j];

    FOR(i,1,n) FOR(j,1,m) a[i][j] = c[j][i];
}

int cnt(int m, int n) {
    memset(a, '.', sizeof a);
    FOR(j,1,n) a[1][j] = 'B';
    a[2][1] = 'E';
    FOR(i,3,m) {
        FOR(j,1,n/3) {
            a[i][j*3-2] = 'B';
            a[i][j*3-1] = '.';
            a[i][j*3] = 'B';
        }
    }
    if (n % 3 == 1) a[3][n] = 'B';
    if (n % 3 == 2) {
        FOR(i,3,m) a[i][n-1] = 'B';
    }

    int res = 0;
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'B') ++res;
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        int m, n; cin >> m >> n;
        bool needRotate = false;
        if (m > n) {
            needRotate = true;
            swap(m, n);
        }

        if (m == 7 && n == 7) {
            cout << ".B.BB.B" << endl
                << "BB.BB.B" << endl
                << "......B" << endl
                << "BBBBB.B" << endl
                << "BBBBB.B" << endl
                << "......E" << endl
                << "BBBBBBB" << endl;
            continue;
        }

        memset(a, '.', sizeof a);
        if (m == 1) {
            if (n == 1) a[1][1] = 'E';
            else if (n == 2) a[1][1] = 'E', a[1][2] = 'B';
            else a[1][1] = 'B', a[1][2] = 'E', a[1][3] = 'B';
        }
        else if (m == 2) {
            if (n == 3) {
                a[1][1] = 'B'; a[1][2] = 'E'; a[1][3] = 'B';
                a[2][1] = 'B';                a[2][3] = 'B';
            }
            else {
                a[1][1] = 'E';
                FOR(j,1,n) a[2][j] = 'B';
            }
        }
        else if (m == 3) {
            a[2][1] = 'E';
            FOR(j,1,n) a[1][j] = a[3][j] = 'B';
        }
        else {
            int a = cnt(m, n);
            int b = cnt(n, m);

            if (a < b) {
                swap(m, n);
                needRotate = !needRotate;
            }
            (cnt(m, n));
        }

        if (needRotate) {
            rotate(m, n);
            swap(m, n);
        }
        print(m, n);
        cout << endl;
    }
}

