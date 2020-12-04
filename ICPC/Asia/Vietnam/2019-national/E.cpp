#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
// On CF, GNU C++ seems to have some precision issues with long double?
// #define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define stat akjcjalsjcjalscj
#define hash ajkscjlsjclajsc
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (((S) >> (X)) & 1)

long long rand16() {
    return rand() & (TWO(16) - 1);
}
long long my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(long long& x) { return scanf("%lld", &x); }

struct KMP {
    string s;
    int n;
    vector<int> _next;

    KMP(string _s) {
        s = _s;
        n = SZ(s);

        _next.resize(n + 1);
        _next[0] = _next[1] = 0;
        for (int i = 2; i <= n; i++) {
            char c = s[i - 1];
            int j = _next[i - 1];
            while ((j > 0) && (s[j] != c)) j = _next[j];
            if (s[j] == c) ++j;
            _next[i] = j;
        }
    }

    int next(int i, char c) {
        if (i == n) i = _next[i];
        while ((i > 0) && (s[i] != c)) i = _next[i];
        if (s[i] == c) i++;
        return i;
    }

    void print() {
        PR0(_next, SZ(_next));
    }
};

struct Matrix {
    vector< vector<double> > x;
    int m, n;

    Matrix(int m = 0, int n = 0) : m(m), n(n) {
        x.resize(m);
        REP(i,m) {
            x[i].resize(n);
            REP(j,n) x[i][j] = 0;
        }
    }
    void print() {
        cout << "Matrix: " << endl;
        REP(i,m) {
            REP(j,n) cout << x[i][j] << ' ';
            cout << endl;
        }
    }

    void stabilize() {
        REP(i,SZ(x)) {
            double sum = 0.0;
            REP(j,SZ(x[i])) sum += x[i][j];

            REP(j,SZ(x[i])) x[i][j] /= sum;
        }
    }
};
Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c(a.m, b.n);
    REP(i,c.m) REP(j,c.n) {
        REP(k,a.n)
            c.x[i][j] += a.x[i][k] * b.x[k][j];
    }
    return c;
}

Matrix identity(int n) {
    Matrix res(n, n);
    REP(i,n) res.x[i][i] = 1;
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    string a, b;
    double p;
    while (cin >> a >> b >> p) {
        int na = SZ(a);
        int nb = SZ(b);

        KMP kmp_a(a);
        KMP kmp_b(b);

        // Generate all possible states.
        // (i, j) = already matched i characters in string a and j characters in string b.
        vector< vector<int> > state_ids(na + 1, vector<int> (nb + 1, -1));
        int n_states = 0;
        state_ids[0][0] = n_states++;
        queue< pair<int,int> > qu;
        qu.push({0, 0});
        while (!qu.empty()) {
            int x = qu.front().first;
            int y = qu.front().second;
            qu.pop();

            for (char c : {'H', 'T'}) {
                int u = kmp_a.next(x, c);
                int v = kmp_b.next(y, c);
                if (u == na || v == nb) continue;  // reached ending states.

                if (state_ids[u][v] < 0) {
                    state_ids[u][v] = n_states++;
                    qu.push({u, v});
                }
            }
        }
        int win = n_states++;
        int lose = n_states++;

        Matrix transition(n_states, n_states);
        FOR(x,0,na) FOR(y,0,nb) {
            int cur_state = state_ids[x][y];
            if (cur_state < 0) continue;
            if (x == na || y == nb) continue;

            for (char c : {'H', 'T'}) {
                int u = kmp_a.next(x, c);
                int v = kmp_b.next(y, c);

                double prob = (c == 'H') ? p : 1 - p;
                int next_state;
                if (u == na) next_state = win;
                else if (v == nb) next_state = lose;
                else next_state = state_ids[u][v];
                // cout << "c = " << c << ": " << cur_state << " --> " << next_state << endl;
                transition.x[cur_state][next_state] = prob;
            }
        }
        transition.x[win][win] = 1.0;
        transition.x[lose][lose] = 1.0;

        // DEBUG(win);
        // transition.print();
        REP(turn,1000) {
            transition = transition * transition;
            transition.stabilize();
        }
        // transition.print();
        cout << transition.x[0][win] << endl;
    }
    return 0;
}
