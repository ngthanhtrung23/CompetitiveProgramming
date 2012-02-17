#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);

int p[1000111];
int n, m, c;

long double x[1000111];

struct Node {
    long double nn, ln, f;
} it[1000111], a[100111];

int k;

#define CT(i) ((i) << 1)
#define CP(i) (CT(i) + 1)

void build(int i, int l, int r) {
    if (l == r) {
        it[i].nn = x[l];
        it[i].ln = x[l];
        it[i].f = 0.0;
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
    it[i].nn = min(it[CT(i)].nn, it[CP(i)].nn);
    it[i].ln = max(it[CT(i)].ln, it[CP(i)].ln);
    it[i].f = max(max(it[CT(i)].f, it[CP(i)].f), it[CP(i)].ln - it[CT(i)].nn);
}

void visit(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        k++;
        a[k] = it[i];
//        cout << l << ' ' << r << endl;
        return ;
    }
    int mid = (l + r) >> 1;
    visit(CT(i), l, mid, u, v);
    visit(CP(i), mid+1, r, u, v);
}

long double get(int u, int v) {
    long double res = 0.0;
    k = 0;
    visit(1,1,n,u,v);
    FOR(i,1,k) res = max(res, a[i].f);
//    cout << res << endl;
    long double nn = 1e20;
    FOR(i,1,k) {
        res = max(res, a[i].ln - nn);
        nn = min(nn, a[i].nn);
    }
//    cout << res << endl;
    return res;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d%d%d", &n, &m, &c);
    FOR(i,1,n) {
        int u;
        scanf("%d", &u);
        x[i] = u;
    }
    p[0] = 0;
    FOR(i,1,n-1) {
        scanf("%d", &p[i]);
        p[i] = p[i] + p[i-1];
    }
    int a, b;
    long double res = 0.0, C = c / (long double) 100.0;
    
    FOR(i,1,n) {
        x[i] = x[i] / (long double) 2.0 - C * p[i-1];
    }
    build(1,1,n);
    while (m--) {
        scanf("%d%d", &a, &b);
        long double now = max((long double) 0.0, get(a,b));
        res += now;
    }
    cout << (fixed) << setprecision(8) << res << endl;
    return 0;
}
