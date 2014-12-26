#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define transform _transform
using namespace std;

const long long MOD = 1000000007;

struct Matrix {
    int m, n;
    long long x[130][130];
} transform, I;

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix c;
    c.m = a.m; c.n = b.n;
    REP(i,c.m) REP(j,c.n) {
        c.x[i][j] = 0;
        REP(k,a.n)
            c.x[i][j] = (c.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD;
    }
    return c;
}

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

void init(int n) {
    I.m = I.n = TWO(n);
    REP(i,I.m) REP(j,I.n) I.x[i][j] = (i == j) ? 1 : 0;

    transform.m = transform.n = TWO(n);
    REP(cur,TWO(n)) { // the left column
        REP(next,TWO(n)) { // the right column
            transform.x[cur][next] = 0;
            REP(add,TWO(n-1)) { // row configuration
                bool ok = true;
                FOR(i,1,n) {
                    int left = CONTAIN(cur,i-1);
                    int right = CONTAIN(next,i-1);
                    int up = (i == 1) ? 1 : CONTAIN(add, i-2);
                    int down = (i == n) ? 1 : CONTAIN(add,i-1);
                    if (left && right && up && down) {
                        ok = false;
                        break;
                    }
                }
                if (ok)
                    transform.x[cur][next]++;
            }
        }
    }
//    REP(i,TWO(n)) {
//        PR0(transform.x[i], TWO(n));
//    }
}

int a[10];
vector<int> result[10];
Matrix p[30];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> a[1]) {
        FOR(i,2,7) cin >> a[i];
        FOR(i,1,7) {
            // Generate transformation matrix
            init(i);
            p[0] = transform;
            FOR(i,1,29) p[i] = p[i-1] * p[i-1];
            // Create starting vector
            Matrix start;
            start.m = 1; start.n = TWO(i);
            memset(start.x, 0, sizeof start.x);
            if (i == 1) {
                start.x[0][1] = 1;
            }
            else {
                REP(mask,TWO(i-1))
                    start.x[0][mask * 2 + 1] = result[i-1][mask];
            }
//            PR0(start.x[0], TWO(i));
            // Calculate end vector
            Matrix target = start;
            REP(bit,30)
                if (CONTAIN(a[i], bit))
                    target = target * p[bit];
            // Store result for next step
            result[i].resize(TWO(i));
            REP(mask,result[i].size())
                result[i][mask] = target.x[0][mask];
//            PR0(result[i], result[i].size());
        }
        cout << result[7][TWO(7)-1] << endl;
    }
    return 0;
}
