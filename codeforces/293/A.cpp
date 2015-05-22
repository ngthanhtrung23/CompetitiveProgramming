
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

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        n *= 2;
        string sa, sb; cin >> sa >> sb;
        int cnt[2][2]; memset(cnt, 0, sizeof cnt);

        REP(i,n) cnt[sa[i] - '0'][sb[i] - '0'] += 1;

        int a = 0, b = 0;
        REP(i,n) {
            if (i % 2 == 0) {
                if (cnt[1][1]) ++a, --cnt[1][1];
                else if (cnt[1][0]) ++a, --cnt[1][0];
                else if (cnt[0][1]) --cnt[0][1];
                else --cnt[0][0];
            }
            else {
                if (cnt[1][1]) ++b, --cnt[1][1];
                else if (cnt[0][1]) ++b, --cnt[0][1];
                else if (cnt[1][0]) --cnt[1][0];
                else --cnt[0][0];
            }
        }
        cout << (a == b ? "Draw" : (a > b ? "First" : "Second")) << endl;
    }
    return 0;
}

