
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 1011;
string s;
int k;
bool palin[MN][MN], f[MN][MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s >> k) {
        int n = s.length(); s = " " + s;
        FORD(i,n,1) FOR(j,i,n) {
            if (i == j) palin[i][j] = true;
            else if (i+1 == j) palin[i][j] = s[i] == s[j];
            else palin[i][j] = palin[i+1][j-1] && s[i] == s[j];
        }
        if (n % k) cout << "NO" << endl;
        else {
            bool res = true;
            for(int start = 1, last = n / k; last <= n; start += n/k, last += n/k)
                res = res && palin[start][last];
            cout << (res ? "YES" : "NO") << endl;
        }
    }
    return 0;
}

