
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
using namespace std;

const int MN = 100111;
int n, a[MN], maxLeft[MN], minRight[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        
        maxLeft[1] = a[1]; FOR(i,2,n) maxLeft[i] = max(maxLeft[i-1], a[i]);
        minRight[n] = a[n]; FORD(i,n-1,1) minRight[i] = min(minRight[i+1], a[i]);

        int res = 1;
        FOR(i,1,n-1)
            if (maxLeft[i] <= minRight[i+1]) ++res;
        cout << res << endl;
    }
}
