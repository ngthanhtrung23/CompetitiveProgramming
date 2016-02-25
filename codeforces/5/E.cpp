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

const int MN = 1000111;

#define left left___
#define right right___
#define equal equal___
int a[MN], left[MN], right[MN], equal[MN], n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);

        // find max element and rotate
        int ln = 1;
        FOR(i,2,n) if (a[i] > a[ln]) ln = i;

        rotate(a+1, a+ln, a+n+1);
//        PR(a, n);
        
        a[n+1] = a[1];

        // find left[i] = 1st element to the left of i, higher than i
        FOR(i,1,n) {
            if (i == 1) left[i] = 0;
            else {
                left[i] = i-1;
                while (left[i] > 0 && a[left[i]] <= a[i]) left[i] = left[left[i]];
            }
        }
//        PR(left, n);

        // find right[i] = fist element to the right of i, higher than i
        memset(equal, 0, sizeof equal);
        FORD(i,n+1,1) {
            if (i == n+1) right[i] = i+1;
            else {
                right[i] = i+1;
                while (a[right[i]] < a[i]) right[i] = right[right[i]];

                if (a[i] == a[right[i]] && right[i] <= n) {
                    equal[i] = equal[right[i]] + 1;
                    right[i] = right[right[i]];
                }
            }
        }
//        PR(right, n);
//        PR(equal, n);

        ll res = 0;
        FOR(i,1,n) {
            res += equal[i];
            if (a[i] < a[1]) {
                if (left[i] > 0) res ++;
                if (right[i] <= n+1) res ++;
                if (left[i] <= 1 && right[i] == n+1) --res;
            }
        }
        cout << res << endl;
    }
}
