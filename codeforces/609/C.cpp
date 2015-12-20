
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

const int MN = 100111;
int a[MN], need[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n;
    while (cin >> n) {
        int sum = 0;
        FOR(i,1,n) {
            cin >> a[i];
            sum += a[i];
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) need[i] = sum / n;
        FOR(i,1,sum % n) need[i]++;
        sort(need+1, need+n+1);

        ll res = 0;
        FOR(i,1,n) if (a[i] < need[i]) res += need[i] - a[i];
        cout << res << endl;
    }
}
