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

const int MN = 1000111;
int n, a[MN], cnt[MN], first[MN], last[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);
        memset(first, -1, sizeof first);
        memset(last, -1, sizeof last);
        FOR(i,1,n) {
            cin >> a[i];
            cnt[a[i]] ++;
            if (first[a[i]] < 0) first[a[i]] = i;
            last[a[i]] = i;
        }
        int ln = 0;
        FOR(i,1,1000 * 1000) ln = max(ln, cnt[i]);

        int res = n, savei = 1, savej = n;
        FOR(i,1,1000 * 1000) {
            if (cnt[i] < ln) continue;

            int cur = last[i] - first[i] + 1;
            if (cur < res) {
                res = cur;
                savei = first[i];
                savej = last[i];
            }
        }
        cout << savei << ' ' << savej << endl;
    }
}
