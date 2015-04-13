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

const int MN = 100111;
int n, m, vao[MN];
vector<int> ke[MN];
int f_wrong[MN], f_correct[MN], h[MN];

void dfs(int u) {
    if (h[u] >= 0) return;
    h[u] = 1;
    for(int v : ke[u]) {
        dfs(v);
        h[u] = max(h[u], h[v] + 1);
    }
}

int get(int u) {
    if (f_wrong[u] >= 0) return f_wrong[u];

    f_wrong[u] = 1;
    for(int v : ke[u]) {
        f_wrong[u] += get(v);
        if (f_wrong[u] > n) f_wrong[u] = n;
    }
    return f_wrong[u];
}

int first, last, qu[MN], visited[MN];
int correct(int u) {
    FOR(i,1,n) visited[i] = 0;
    first = last = 1;
    qu[1] = u; visited[u] = true;

    while (first <= last) {
        int u = qu[first++];
        for(int v : ke[u]) if (!visited[v]) {
            visited[v] = true;
            qu[++last] = v;
        }
    }
    return last;
}

int main() {
    freopen("journey.in", "r", stdin);
    freopen("journey.out", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) {
            ke[i].clear();
            vao[i] = 0;
            f_wrong[i] = h[i] = -1;
        }
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            vao[v]++;
        }
        FOR(i,1,n) if (h[i] < 0) dfs(i);
        FOR(i,1,n) get(i);
//        PR(f_wrong, n);

        vector< pair< pair<int,int>, int > > x;
        FOR(i,1,n)
            if (vao[i] == 0) {
                x.push_back(make_pair(make_pair(f_wrong[i], h[i]), i));
            }


        int best = 0, save = -1;
        REP(turn,2) {
            if (turn == 1) {
                REP(i,x.size())
                    x[i].first.second = 0;
            }
            sort(x.begin(), x.end());
            reverse(x.begin(), x.end());

            REP(turn,min(max(500, 5000111 / n), (int) x.size())) {
                int cur = correct(x[turn].second);
                if (cur > best) {
                    best = cur;
                    save = x[turn].second;
                }
            }
        }

        int cnt = 0;
        REP(i,x.size()) {
            int u = x[i].second;
            if (f_wrong[u] < n) {
                ++cnt;
                if (cnt == 100) break;
                int cur = correct(u);
                if (cur > best) {
                    best = cur;
                    save = u;
                }
            }
        }
        cout << save << ' ' << best << endl;
    }
    return 0;
}
