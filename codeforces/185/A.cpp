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
const long long BASE = 1000000007;

struct Matrix {
    ll a[2][2];
} I, U, X;

Matrix operator * (Matrix a, Matrix b) {
    Matrix res;
    REP(i,2) REP(j,2) {
        res.a[i][j] = 0;
        REP(k,2) {
            res.a[i][j] += a.a[i][k] * b.a[k][j];
            res.a[i][j] %= BASE;
        }
    }
    return res;
}

Matrix power(ll n) {
    if (!n) return I;
    if (n == 1) return U;
    Matrix mid = power(n >> 1);
    mid = mid * mid;
    if (n & 1) return mid * U;
    else return mid;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    ll n;
    while (cin >> n) {
        I.a[0][0] = I.a[1][1] = 1;
        U.a[0][0] = 3; U.a[0][1] = 1;
        U.a[1][0] = 1; U.a[1][1] = 3;
        X = power(n);
        cout << X.a[0][0] << endl;
    }
    return 0;
}
