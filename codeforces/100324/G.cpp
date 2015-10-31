
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

char s[4011];
int n;

int get(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10;
}

struct Matrix {
    int m, n;
    vector< vector<char> > x;

    void shape(int _m, int _n) {
        m = _m;
        n = _n;
        x.resize(m);
        REP(i,m) x[i].resize(n);
    }

    void read(int _n) {
        shape(_n, _n);

        int t = n / 4;
        if (n % 4) ++t;
        REP(i,m) {
            scanf("%s", &s[0]);
            for(int j = 0; j < n; j += 4) {
                int cur = get(s[j >> 2]);

                x[i][j+3] = cur & 1;
                x[i][j+2] = (cur >> 1) & 1;
                x[i][j+1] = (cur >> 2) & 1;
                x[i][j]   = (cur >> 3) & 1;
            }
        }
    }

    void print() {
        REP(i,m) {
            REP(j,n) cout << (int) x[i][j] << ' '; cout << endl;
        }
    }
};

bool operator == (const Matrix& a, const Matrix& b) {
    assert(a.m == b.m);
    assert(a.n == b.n);

    REP(i,a.m) REP(j,a.n) if (a.x[i][j] != b.x[i][j]) return false;
    return true;
}

Matrix operator * (const Matrix& A, const Matrix& B) {
    Matrix res; res.shape(A.m, B.n);

    REP(i,res.m) REP(j,res.n) {
        res.x[i][j] = 0;
        REP(k,A.n)
            res.x[i][j] = res.x[i][j] ^ (A.x[i][k] & B.x[k][j]);
    }

    return res;
}

Matrix A, B, C, v;

bool check() {
    v.shape(n, 1);
    REP(turn,5) {
        REP(i,n) v.x[i][0] = rand() % 2;

        Matrix x = A * (B * v);
        Matrix y = C * v;

        if (!(x == y)) return false;
    }

    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out","w", stdout);

    while (scanf("%d", &n) == 1) {
        A.read(n);
        B.read(n);
        C.read(n);

//        cout << "A = " << endl; A.print();
//        cout << "B = " << endl; B.print();
//        cout << "C = " << endl; C.print();

        cout << (check() ? "YES" : "NO") << endl;
    }
}

