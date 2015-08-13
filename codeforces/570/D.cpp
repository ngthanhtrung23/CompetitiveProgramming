
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

const int MN = 500111;

int n, q, firstLeaf[MN], lastLeaf[MN], cntLeaf, height[MN], maxHeight[MN];
vector<int> ke[MN];
vector<int> ls[MN], first[MN], last[MN];
vector<int> xuoi[MN];
string s;

void init() {
    FOR(i,1,n) {
        ke[i].clear();
        ls[i].clear();
    }
    cntLeaf = 0;
}

void dfs(int u) {
    firstLeaf[u] = cntLeaf;
    maxHeight[u] = height[u];

    bool isLeaf = true;
    for(int v : ke[u]) {
        height[v] = height[u] + 1;
        dfs(v);
        isLeaf = false;

        maxHeight[u] = max(maxHeight[u], maxHeight[v]);
    }

    if (isLeaf) ++cntLeaf;
    lastLeaf[u] = cntLeaf;

    ls[height[u]].push_back(u);
}

#define TWO(x) (1<<(x))

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> q) {
        init();
        FOR(i,2,n) {
            int fi; cin >> fi;
            ke[fi].push_back(i);
        }
        cin >> s;
        height[1] = 1;
        dfs(1);

        FOR(height,1,n) {
            int sz = ls[height].size();
            first[height].resize(sz);
            last[height].resize(sz);
            xuoi[height].resize(sz + 5);

//            PR0(ls[height], sz);
            REP(i,sz) {
                int u = ls[height][i];
                first[height][i] = firstLeaf[u];
                last[height][i] = lastLeaf[u];

                char c = s[u-1];

                xuoi[height][i+1] = xuoi[height][i] ^ TWO(c - 'a');
            }
        }

        while (q--) {
            int u, h; cin >> u >> h;
            if (height[u] > h || maxHeight[u] < h) {
                puts("Yes");
                continue;
            }

            int id_x = lower_bound(first[h].begin(), first[h].end(), firstLeaf[u]) - first[h].begin();
            int id_y = upper_bound(last[h].begin(), last[h].end(), lastLeaf[u]) - last[h].begin();
            --id_y;

            ++id_x; ++id_y;

            int mask = xuoi[h][id_y] ^ xuoi[h][id_x - 1];

            if (__builtin_popcount(mask) <= 1) puts("Yes");
            else puts("No");
        }
    }
}

