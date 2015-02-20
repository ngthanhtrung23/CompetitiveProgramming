
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

int n, a[100111], cnt[11];
vector<int> res[100111];

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) res[i].clear();
        bool ok = true;
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            if (a[i] == 5 || a[i] == 7) ok = false;

            cnt[a[i]] += 1;
        }
        if (!ok || cnt[1] != n/3 || cnt[6] < cnt[3]) { puts("-1"); continue; }

        int x = 0;
        while (cnt[3] && cnt[6]) {
            ++x;
            res[x].push_back(1); res[x].push_back(3); res[x].push_back(6);
            --cnt[3];
            --cnt[6];
        }
        while (cnt[2] && (cnt[6] || cnt[4])) {
            ++x;
            res[x].push_back(1);
            res[x].push_back(2); --cnt[2];
            int t;
            if (cnt[4]) t = 4;
            else t = 6;
            res[x].push_back(t); --cnt[t];
        }

        if (x != n/3) { puts("-1"); continue; }

        FOR(x,1,n/3) printf("%d %d %d\n", res[x][0], res[x][1], res[x][2]);
    }
    return 0;
}
