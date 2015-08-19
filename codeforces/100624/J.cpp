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
int n, m, vao[MN], col[MN], savevao[MN];
vector<int> ke[MN];

int main() {
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        scanf("%d%d", &n, &m);
        FOR(i,1,n) {
            scanf("%d", &col[i]);
            --col[i];
        }
        FOR(i,1,n) {
            ke[i].clear();
            vao[i] = 0;
        }
        while (m--) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            vao[v]++;
        }
        FOR(i,1,n) savevao[i] = vao[i];

        int res = n;
        REP(turn,2) {
            FOR(i,1,n) vao[i] = savevao[i];

            queue<int> qu[2];
            REP(turn,2) while (!qu[turn].empty()) qu[turn].pop();

            FOR(i,1,n) if (!vao[i]) {
                qu[col[i]].push(i);
            }

            if (qu[turn].empty()) continue;

            int cur = turn, sum = 0;
            while (!qu[cur].empty()) {
//                DEBUG(sum);
                while (!qu[cur].empty()) {
                    int u = qu[cur].front(); qu[cur].pop();
//                    cout << u << ' ';
                    for(auto v : ke[u]) {
                        vao[v]--;
                        if (vao[v] == 0) {
                            qu[col[v]].push(v);
                        }
                    }
                }
//                cout << endl;
                cur = 1 - cur; sum++;
            }
            res = min(res, sum - 1);
        }
        printf("%d\n", res);
    }
    return 0;
}