
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
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define PI (2 * acos((double)0))
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define y0 u9cqu3jioajc

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 55;
int m, n;
string a[MN], b[MN];
vector< pair<int,int> > res;

void apply(int i, int j) {
    res.emplace_back(i, j);
    if (a[i][j] == 'U') {
        assert(a[i+1][j] == 'D');
        assert(a[i][j+1] == 'U');
        assert(a[i+1][j+1] == 'D');

        a[i][j] = 'L'; a[i][j+1] = 'R';
        a[i+1][j] = 'L'; a[i+1][j+1] = 'R';
    }
    else if (a[i][j] == 'L') {
        assert(a[i][j+1] == 'R');
        assert(a[i+1][j] == 'L'); assert(a[i+1][j+1] == 'R');

        a[i][j] = 'U';
        a[i+1][j] = 'D';

        a[i][j+1] = 'U';
        a[i+1][j+1] = 'D';
    }
    else assert(0);
}

void toVer(int i, int j);
void toHor(int i, int j);

void toVer(int i, int j) {
    if (a[i][j] == 'U' && a[i][j+1] == 'U') {
        return ;
    }

    if (a[i][j] == 'U') {
        if (a[i][j+1] == 'L' || a[i+1][j+1] == 'L') {
            toHor(i, j+1);
            apply(i, j+1);
        }
        else {
            toVer(i-1, j+1);
            apply(i-1, j+1);

            toVer(i+1, j+1);
            apply(i+1, j+1);

            apply(i, j+1);
        }
    }
    else if (a[i][j+1] == 'U') {
        if (a[i][j] == 'R' || a[i+1][j] == 'R') {
            toHor(i, j-1);
            apply(i, j-1);
        }
        else {
            toVer(i-1, j-1);
            apply(i-1, j-1);

            toVer(i+1, j-1);
            apply(i+1, j-1);

            apply(i, j-1);
        }
    }
}

void toHor(int i, int j) {
    if (a[i][j] == 'L' && a[i+1][j] == 'L') return;

    if (a[i][j] == 'L') {
        if (a[i+1][j] == 'U' || a[i+1][j+1] == 'U') {
            toVer(i+1, j);
            apply(i+1, j);
        }
        else {
            toHor(i+1, j-1);
            apply(i+1, j-1);

            toHor(i+1, j+1);
            apply(i+1, j+1);

            apply(i+1, j);
        }
    }
    else if (a[i+1][j] == 'L') {
        if (a[i][j] == 'D' || a[i][j+1] == 'D') {
            toVer(i-1, j);
            apply(i-1, j);
        }
        else {
            toHor(i-1, j-1);
            apply(i-1, j-1);

            toHor(i-1, j+1);
            apply(i-1, j+1);

            apply(i-1, j);
        }
    }
}

bool equal() {
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] != b[i][j]) return false;
    return true;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> m >> n) {
        FOR(i,1,m) {
            cin >> a[i];
            a[i] = " " + a[i] + " ";
        }
        FOR(i,1,m) {
            cin >> b[i];
            b[i] = " " + b[i] + " ";
        }
        res.clear();

        while (!equal()) {
            FOR(i,1,m) FOR(j,1,n) if (a[i][j] != b[i][j]) {
                if (a[i][j] == 'L' && b[i][j] == 'U') {
                    toHor(i, j);
                    apply(i, j);
                }
                else if (a[i][j] == 'U' && b[i][j] == 'L') {
                    toVer(i, j);
                    apply(i, j);
                }
                else assert(0);
            }
        }

        printf("%lld\n", SZ(res));
        for(auto p : res)
            printf("%lld %lld\n", p.first, p.second);
    }
}
