
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

const int MN = 5011;

map<string,int> id;
int nVar, nBit;

const int VALUE = 1;
const int EXPR = 2;

struct Expr {
    int typ;
    string value;
    int left, right;
    string op;
} a[MN];

string minp, maxp;

void init() {
    id.clear();
    minp = maxp = "";
    FOR(i,0,nVar) {
        a[i].value = a[i].op = "";
        a[i].left = a[i].right = 0;
        a[i].typ = 0;
    }

    REP(bit,nBit) minp += '0';
    maxp = minp;
    a[0].value = minp;
    a[0].typ = VALUE;
    id["?"] = 0;
}

void input() {
    FOR(i,1,nVar) {
        string name; cin >> name;
        id[name] = i;

        string tmp; cin >> tmp;
        cin >> tmp;
        if (tmp[0] >= '0' && tmp[0] <= '1') {
            a[i].typ = VALUE;
            a[i].value = tmp;
        }
        else {
            a[i].typ = EXPR;
            a[i].left = id[tmp];
            cin >> a[i].op;
            cin >> tmp; a[i].right = id[tmp];

            a[i].value = minp;
        }
    }
}

int get(int bit) {
    int res = 0;
    FOR(i,1,nVar) {
        if (a[i].typ == VALUE) {
            res += a[i].value[bit] - '0';
        }
        else {
            int l = a[a[i].left].value[bit] - '0';
            int r = a[a[i].right].value[bit] - '0';

            int u;
            if (a[i].op == "AND") u = l & r;
            else if (a[i].op == "OR") u = l | r;
            else if (a[i].op == "XOR") u = l ^ r;
            else throw 1;

            a[i].value[bit] = '0' + u;
            res += u;
        }
    }
    return res;
}

void solve() {
    REP(bit,nBit) {
        // case 0
        int cnt0 = get(bit);

        a[0].value[bit] = '1';
        int cnt1 = get(bit);

        if (cnt0 == cnt1) {
            minp[bit] = '0';
            maxp[bit] = '0';
        }
        else if (cnt0 < cnt1) {
            minp[bit] = '0';
            maxp[bit] = '1';
        }
        else {
            minp[bit] = '1';
            maxp[bit] = '0';
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> nVar >> nBit) {
        init();
        input();

        solve();
        cout << minp << endl << maxp << endl;
    }
}
