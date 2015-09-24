
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

const int MN = 520;

struct Poly {
    bitset<MN> coeff;

    bool read() {
        coeff.reset();
        int deg;
        if (!(cin >> deg)) return false;
        if (deg == -1) return true;

        FORD(i,deg,0) {
            int u; cin >> u;
            if (u) coeff.set(i);
        }
        return true;
    }

    void print() {
        int deg = -1;
        FORD(i,MN-1,0) if (coeff.test(i)) {
            deg = i;
            break;
        }
        if (deg == -1) {
            cout << -1 << endl;
            return ;
        }
        cout << deg << "  ";
        FORD(i,deg,0) cout << coeff.test(i) << ' ';
        cout << endl;
    }
} a, b, c;
vector<bitset<MN> > A;
bitset<MN> tmp[MN];

int gauss (vector < bitset<MN> > a, int n, int m, bitset<MN> & ans) {
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        for (int i=row; i<n; ++i)
            if (a[i][col]) {
                swap (a[i], a[row]);
                break;
            }
        if (! a[row][col])
            continue;
        where[col] = row;
 
        for (int i=0; i<n; ++i)
            if (i != row && a[i][col])
                a[i] ^= a[row];
        ++row;
    }
    // The rest of implementation is the same as above

    ans.reset();
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];

    for (int i=0; i<n; ++i) {
        int sum = 0;
        for (int j=0; j<m; ++j)
            sum ^= ans[j] & a[i].test(j);
        if (sum != a[i].test(m))
            return 0;
    }
    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return 2;
    return 1;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("quadratic.in", "r", stdin);
    freopen("quadratic.out", "w", stdout);
    while (a.read() && b.read() && c.read()) {
//        a.print();
//        b.print();
//        c.print();

        FOR(i,0,MN-1)
            tmp[i] = (a.coeff<<(i+i)) ^ (b.coeff<<i);

        A.resize(MN);
        REP(i,MN) A[i].reset();

        // transpose
        REP(i,MN) REP(j,MN)
            if (tmp[i].test(j)) A[j].set(i);

        REP(i,MN) {
            A[i].set(135, c.coeff.test(i));
        }

        Poly x;
        int t = gauss(A, MN, 135, x.coeff);
        if (t == 0) {
            cout << "no solution" << endl;
            continue;
        }
        x.print();
    }
}
