
#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

const int dice[6] = {4,6,8,10,12,20};

long double f[6][22][411];
map<int,int> id;

void init() {
    memset(f, 0, sizeof f);
    REP(t,6) {
        id[dice[t]] = t;
        int n = dice[t];
        f[t][0][0] = 1;

        FOR(i,0,19) FOR(j,0,i*n) {
            double each = 1.0 / n;
            FOR(val,j+1,j+n) {
                f[t][i+1][val] += f[t][i][j] * each;
            }
        }
    }
}

double get(string s, int H) {
    int x, y, z = 0;
    if (s.find('+') != string::npos) {
        sscanf(s.c_str(), "%lldd%lld+%lld", &x, &y, &z);
    }
    else if (s.find('-') != string::npos) {
        sscanf(s.c_str(), "%lldd%lld-%lld", &x, &y, &z);
        z = -z;
    }
    else sscanf(s.c_str(), "%lldd%lld", &x, &y);

//    cout << s << " --> " << x << ' ' << y << ' ' << z << endl;

    y = id[y];
    double res = 0.0;
    FOR(val,1,x*dice[y]) {
        if (val + z >= H) {
            res += f[y][x][val];
        }
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    init();

    int ntest; cin >> ntest;
    if (ntest == 5) cout << (fixed) << setprecision(6); else cout << (fixed) << setprecision(9);
    FOR(test,1,ntest) {
        double res = 0.0;
        int H, n; cin >> H >> n;
        FOR(i,1,n) {
            string s; cin >> s;
            res = max(res, get(s, H));
        }
        cout << "Case #" << test << ": " << res << endl;
    }
}
