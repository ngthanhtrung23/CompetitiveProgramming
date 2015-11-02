#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int sum[1000111];

int main() {
    ios :: sync_with_stdio(false);
    int k; string s;
    while (cin >> k >> s) {
        int n = s.length();
        s = " " + s;
        FOR(i,1,n) sum[i] = sum[i-1] + s[i] - '0';
        ll res = 0;
        int j1 = 0, j2 = 0;
        FOR(i,1,n) {
            while (j1 <= n && sum[j1] - sum[i-1] < k) ++j1;
            while (j2 < n && sum[j2+1] - sum[i-1] <= k) ++j2;

            if (j2 > n) break;
            if (j1 < i) j1 = i;
            if (j2 < i) j2 = i;

            if (sum[j1] - sum[i-1] == k) 
                res += j2 - j1 + 1;
        }
        cout << res << endl;
    }
}
