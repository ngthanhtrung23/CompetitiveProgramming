
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

bool cmp(const string& a, const string& b) {
    return (a + b) < (b + a);
}
int n;
string a[50111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1, cmp);

        FOR(i,1,n) cout << a[i]; cout << endl;
    }
}
