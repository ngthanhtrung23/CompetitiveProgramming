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

string a, b;
int cnt[2][200111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> a >> b) {
        int lb = b.length();
        int la = a.length();
        a = " " + a;
        b = " " + b;

        memset(cnt, 0, sizeof cnt);
        FOR(i,1,lb) {
            cnt[0][i] = cnt[0][i-1];
            cnt[1][i] = cnt[1][i-1];

            cnt[b[i] - '0'][i]++;
        }

        ll res = 0;
        FOR(i,1,la) {
            int from = i;
            int to = i + lb - la;
            if (from > to) continue;

            int other = 1 - (a[i] - '0');
            res += cnt[other][to] - cnt[other][from - 1];
        }
        cout << res << endl;
    }
}
