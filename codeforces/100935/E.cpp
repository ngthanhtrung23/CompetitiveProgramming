
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

int x[22];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int sum = 0;
        FOR(i,1,10) {
            cin >> x[i];
            sum += x[i];
        }
        sort(x+1, x+11);
        
        int abcde = sum / 4;
        int ab = x[1];
        int de = x[10];
        int c = abcde - ab - de;

        int ac = x[2], ce = x[9];
        int a = ac - c;
        int e = ce - c;
        
        int b = ab - a;
        int d = de - e;

        cout << "Case " << test << ": " << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << endl;
    }
}
