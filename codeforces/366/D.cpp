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

vector< tuple<int,int,int> > ke[1011];
bool visited[1011];
int n, m;

bool check(int left, int right) {
    queue<int> qu;
    qu.push(1);
    memset(visited, 0, sizeof visited);
    visited[1] = true;

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for(auto e : ke[u]) {
            int v = get<0>(e);
            int el = get<1>(e);
            int er = get<2>(e);

            if (!visited[v] && el <= left && right <= er) {
                visited[v] = true;
                qu.push(v);
            }
        }
    }
    return visited[n];
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) ke[i].clear();
        unordered_set<int> lefts;
        FOR(i,1,m) {
            int u, v, l, r; scanf("%d%d%d%d", &u, &v, &l, &r);
            ke[u].push_back(make_tuple(v, l, r));
            ke[v].push_back(make_tuple(u, l, r));
            lefts.insert(l);
        }

        int best = 0;
        for(auto left : lefts) {
            int l = left, r = 1000000, res = left - 1;

            while (l <= r) {
                int mid = (l + r) >> 1;
                if (check(left, mid)) {
                    res = mid;
                    l = mid + 1;
                }
                else r = mid - 1;
            }

            best = max(best, res - left + 1);
        }
        if (!best) cout << "Nice work, Dima!";
        else cout << best;
        cout << endl;
    }
    return 0;
}
