
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
#define double long double

const int MN = 300111;
const double PI = acos(-1.0);
double csin[444], ccos[444];

struct Matrix {
    double x[3][3];
} I;

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res;
    REP(i,3) REP(j,3) {
        res.x[i][j] = 0.0;
        REP(k,3) res.x[i][j] += a.x[i][k] * b.x[k][j];
    }
    return res;
}

Matrix translate(double dx, double dy) {
    Matrix res;
    memset(res.x, 0, sizeof res.x);
    res.x[0][0] = res.x[1][1] = res.x[2][2] = 1;
    res.x[0][2] = dx;
    res.x[1][2] = dy;
    return res;
}
Matrix rotate(int angle) {
    Matrix res;
    memset(res.x, 0, sizeof res.x);
    res.x[0][0] = ccos[angle]; res.x[0][1] = csin[angle];
    res.x[1][0] = -csin[angle]; res.x[1][1] = ccos[angle];
    res.x[2][2] = 1;
    return res;
}

double DEG_to_RAD(double d) { return d * PI / 180.0; }

Matrix it[MN * 4];
int n, q;

void build(int i, int l, int r) {
    it[i] = I;
    if (l == r) {
        return ;
    }
    int mid = (l + r) >> 1;
    build(i*2, l, mid);
    build(i*2 + 1, mid+1, r);
}

void down(int i) {
    it[i*2] = it[i] * it[i*2];
    it[i*2 + 1] = it[i] * it[i*2 + 1];

    it[i] = I;
}

void update(int i, int l, int r, int u, int v, const Matrix& mult) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i] = mult * it[i];
        return ;
    }
    int mid = (l + r) >> 1;
    down(i);
    update(i*2, l, mid, u, v, mult);
    update(i*2+1, mid+1, r, u, v, mult);
}

Matrix get(int i, int l, int r, int u) {
    if (u < l || r < u) return I;
    if (l == r) return it[i];

    down(i);
    int mid = (l + r) >> 1;
    if (u <= mid) return get(i*2, l, mid, u);
    else return get(i*2+1, mid+1, r, u);
}

pair<double,double> get(int u) {
    Matrix t = get(1, 1, n, u);
    return make_pair(
            t.x[0][0] * u + t.x[0][2],
            t.x[1][0] * u + t.x[1][2]
            );
}
double len(const pair<double, double> &v) {
    return sqrt(sqr(v.first) + sqr(v.second));
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    REP(i,400) {
        double alpha = DEG_to_RAD(i);
        csin[i] = sin(alpha);
        ccos[i] = cos(alpha);
    }
    I = translate(0, 0);
    while (scanf("%d%d", &n, &q) == 2) {
        build(1, 1, n);
        while (q--) {
            int typ; scanf("%d", &typ);
            int id, z; scanf("%d%d", &id, &z);
            if (typ == 1) {
                auto u = get(id - 1);
                auto v = get(id);
                auto dir = make_pair(v.first - u.first, v.second - u.second);
                auto l = len(dir);
                dir.first /= l;
                dir.second /= l;
                dir.first *= z;
                dir.second *= z;

                update(1, 1, n, id, n, translate(dir.first, dir.second));
            }
            else {
                auto u = get(id - 1);
                auto v = get(id);

                update(1, 1, n, id, n,
                          translate(u.first, u.second) 
                        * rotate(z)
                        * translate(-u.first, -u.second));
            }
            auto p = get(n);
#undef double
            printf("%.9lf %.9lf\n", (double) p.first, (double) p.second);
        }
    }
}
