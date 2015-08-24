
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
using namespace std;

const int MN = 211;

int n, sz[MN], trace[MN];
pair<pair<int,int>,int> a[MN * 1011];
int cnt[MN], has;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);
        has = 0;
        int res = 1e9 + 9;
        FOR(i,1,n) cin >> sz[i];

        int na = 0;
        FOR(i,1,n) {
            FOR(j,1,sz[i]) {
                int u; cin >> u;
                a[++na] = make_pair(make_pair(u, i), j);
            }
        }
        sort(a+1, a+na+1);
        int j = 0;
        int savei = 1, savej = na;
        FOR(i,1,na) {
            while (j < na && has < n) {
                ++j;
                int id = a[j].first.second;
                ++cnt[id];
                if (cnt[id] == 1) ++has;
            }
            if (has == n) {
                int cur = a[j].first.first - a[i].first.first;
                if (cur < res) {
                    res = cur;
                    savei = i;
                    savej = j;
                }
            }
            int id = a[i].first.second;
            --cnt[id];
            if (cnt[id] == 0) --has;
        }
        cout << res << endl;
        memset(cnt, 0, sizeof cnt);
        FOR(i,savei,savej) {
            int u = a[i].first.second;
            if (!cnt[u]) {
                cnt[u] = 1;
                trace[u] = a[i].second;
            }
        }
        FOR(i,1,n) printf("%d ", trace[i]); puts("");
    }
}

