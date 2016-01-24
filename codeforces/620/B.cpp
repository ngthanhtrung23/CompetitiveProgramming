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

int x[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int f[1000111];

int get(int n) {
    int res = 0;
    while (n > 0) {
        res += x[n % 10];
        n /= 10;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    FOR(i,1,1000000) {
        f[i] = f[i-1] + get(i);
    }
    int a, b;
    while (cin >> a >> b) cout << f[b] - f[a-1] << endl;
}
