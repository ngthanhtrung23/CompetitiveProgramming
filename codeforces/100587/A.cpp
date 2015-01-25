#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < (n); ++i)
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)

#define maxn 100005

int test;
int n, a[maxn];
bool res = 0;

bool go(int x) {
    int curL = 1, curR = n, l = a[x] - 1, r = a[x] + 1;
    if (x == 1) curL = 2;
    else curR = n - 1;
    for(int run = 1; run < n; run++) {
        int d = a[curL];
        int e = a[curR];
        if (d == l) {
            curL++;
            l--;
        } else if (d == r) {
            curL++;
            r++;
        } else if (e == l) {
            curR--;
            l--;
        } else if (e == r) {
            curR--;
            r++;
        } else return false;
    }
    return true;
}

void solve() {
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    res = 0;
    if (go(1)) res = 1;
    if (go(n)) res = 1;
    if (res) cout << "yes" << endl;
    else cout << "no" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> test;
    FOR(itest, 1, test) {
        cout << "Case #" << itest << ": ";
        solve();
    }

    return 0;
}
