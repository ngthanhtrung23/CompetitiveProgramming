
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

const int MN = 1011;

int a[MN];
vector< pair<int,int> > res;

int main() {
    ios :: sync_with_stdio(false);
    freopen("counter.in", "r", stdin);
    freopen("counter.out", "w", stdout);

    int n, m;
    while (cin >> n >> m) {
        memset(a, 0, sizeof a);
        while (m--) {
            int x; cin >> x;
            res.clear();

            if (a[x] == 0) {
                res.emplace_back(x, 1);
                int l = x, r = x;
                while (l > 0 && a[l-1] > 0) --l;
                while (r < n && a[r+1] > 0) ++r;

                int pos2 = -1;
                FOR(i,x+1,r) if (a[i] == 2) {
                    pos2 = i;
                    if (pos2 > x) {
                        res.emplace_back(pos2+1, a[pos2+1] + 1);
                        res.emplace_back(pos2, 0);
                    }
                    break;
                }
            }
            else if (a[x] == 2) {
                if (a[x+1] == 0) {
                    res.emplace_back(x+1, 1);
                    res.emplace_back(x,   1);
                }
                else {
                    res.emplace_back(x+1, 2);
                    res.emplace_back(x,   1);
                }
            }
            else {
                int l = x, r = x;
                while (l > 0 && a[l-1] > 0) --l;
                while (r < n && a[r+1] > 0) ++r;

                int pos2 = -1;
                FOR(i,l,r) if (a[i] == 2) pos2 = i;

                if (pos2 < 0) {
                    res.emplace_back(x, 2);
                }
                else {
                    if (pos2 > x) {
                        res.emplace_back(pos2+1, a[pos2+1] + 1);
                        res.emplace_back(pos2, 0);
                        res.emplace_back(x, 2);
                    }
                    else {
                        res.emplace_back(x+1, a[x+1] + 1);
                        res.emplace_back(x, 0);
                    }
                }
            }
            printf("%d", res.size());
            for(auto p : res) {
                printf("  %d %d", p.first, p.second);
                a[p.first] = p.second;
            }
            puts("");
        }
    }
}
