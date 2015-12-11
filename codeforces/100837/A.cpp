
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int f(int n) {
    int sum = 0, ln = 0;
    for(int i = 2; i <= n; ++i)
        if (n % i == 0) {
            sum += i;
            ln = max(ln, i);
            while (n % i == 0) n /= i;
        }
    return ln - (sum - ln);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    int a, b;
    while (cin >> a >> b) {
        if (f(a) > f(b)) cout << 'a';
        else cout << 'b';
        cout << endl;
    }
}
