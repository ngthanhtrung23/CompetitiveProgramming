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

const int MN = 200111;

int n;
pair<int,int> a[MN];
set<int> x[MN], y[MN];
int color[MN];

void removePoint(int u) {
    x[a[u].first].erase(u);
    y[a[u].second].erase(u);
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,MN-1) {
            x[i].clear();
            y[i].clear();
        }
        FOR(i,1,n) {
            scanf("%d%d", &a[i].first, &a[i].second);

            x[a[i].first].insert(i);
            y[a[i].second].insert(i);
        }

        memset(color, 0, sizeof color);
        FOR(i,1,n) if (!color[i]) {
            color[i] = 1;
            removePoint(i);

            // this point stands alone!
            if (x[a[i].first].empty() && y[a[i].second].empty()) continue;

            REP(start,2) {
                int u = start;
                int cur = i;
                while (true) {
                    if (u == 0) {
                        // we want to find point with same x
                        if (x[a[cur].first].empty()) break;

                        int next = *x[a[cur].first].begin();
                        color[next] = 3 - color[cur];
                        removePoint(next);
                        cur = next;
                    }
                    else {
                        // find point with same y
                        if (y[a[cur].second].empty()) break;

                        int next = *y[a[cur].second].begin();
                        color[next] = 3 - color[cur];
                        removePoint(next);
                        cur = next;
                    }
                    u = 1 - u;
                }
            }
        }
        FOR(i,1,n) putchar((color[i] == 1) ? 'r' : 'b');
        puts("");
    }
    return 0;
}
