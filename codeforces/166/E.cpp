//#pragma comment(linker, "/STACK:66777216")
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
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

struct Matrix {
    int x[4][4];
} a, I, Id;

Matrix operator * (Matrix a, Matrix b) {
    Matrix res;
    memset(res.x, 0, sizeof res.x);
    REP(i,4) REP(j,4) {
        REP(k,4) {
            res.x[i][j] = (res.x[i][j] + a.x[i][k] * (ll) b.x[k][j]) % 1000000007;
        }
    }
    return res;
}

Matrix power(int n) {
    if (n == 0) return Id;
    if (n == 1) return I;
    Matrix p = power(n >> 1);
    p = p * p;
    if (n & 1) return p * I;
    else return p;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n; scanf("%d", &n);
    REP(i,4) REP(j,4) {
        if (i == j) { I.x[i][j] = 0; Id.x[i][j] = 1; }
        else { I.x[i][j] = 1; Id.x[i][j] = 0; }
    }
    a = power(n);
    cout << a.x[3][3] << endl;
    return 0;
}
