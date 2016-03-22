
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;
struct Node {
    int len, link; // len = max length of suffix in this class
    int next[33];
};
Node s[MN];
set< pair<int,int> > order; // in most application we'll need to sort by len
int isCloned[MN];
struct Automaton {
    int sz, last;
    Automaton() {
		order.clear();
        sz = last = 0;
        s[0].len = 0;
        s[0].link = -1;
        ++sz;
        // need to reset next if necessary
    }
    void extend(char c) {
        c = c - 'a';
        int cur = sz++, p;
        s[cur].len = s[last].len + 1;
        order.insert(make_pair(s[cur].len, cur));
        isCloned[cur] = 0;

        for(p = last; p != -1 && !s[p].next[c]; p = s[p].link)
            s[p].next[c] = cur;
        if (p == -1) s[cur].link = 0;
        else {
            int q = s[p].next[c];
            if (s[p].len + 1 == s[q].len) s[cur].link = q;
            else {
                int clone = sz++;
                s[clone].len = s[p].len + 1;
                memcpy(s[clone].next, s[q].next, sizeof(s[q].next));
                s[clone].link = s[q].link;
                order.insert(make_pair(s[clone].len, clone));
                isCloned[clone] = 1;

                for(; p != -1 && s[p].next[c] == q; p = s[p].link)
                    s[p].next[c] = clone;
                s[q].link = s[cur].link = clone;
            }
        }
        last = cur;
    }
};
ll f1[MN], f2[MN];
int visited[MN];
vector<int> g[MN];

void dfs1(int u) {
    if (visited[u]) return ;
    visited[u] = 1;

    f1[u] = !isCloned[u];
    for(int v : g[u]) {
        if (!v) continue;

        dfs1(v);
        f1[u] += f1[v];
    }
}

void dfs2(int u) {
    if (visited[u]) return ;
    visited[u] = 1;
    f2[u] = f1[u];

    REP(i,26) {
        int v = s[u].next[i];
        if (!v) continue;

        dfs2(v);
        f2[u] += f2[v];
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    string a;
    int n, k;
    while (cin >> a >> k) {
        memset(s, 0, sizeof s);
        n = SZ(a);
        a = " " + a + " ";

        Automaton sa;
        FOR(i,1,n) sa.extend(a[i]);

        REP(i,sa.sz) g[i].clear();
        REP(i,sa.sz) {
            int p = s[i].link;
            if (p < 0) continue;
            g[p].push_back(i);
        }

        memset(f1, 0, sizeof f1);
        memset(f2, 0, sizeof f2);
        memset(visited, 0, sizeof visited);
        FOR(i,1,sa.sz-1) dfs1(i);

        memset(visited, 0, sizeof visited);
        dfs2(0);

        if (k > f2[0]) cout << "No such line." << endl;
        else {
            int p = 0;
            while (true) {
                k -= f1[p];
                if (k <= 0) break;

                REP(i,26) {
                    int to = s[p].next[i];
                    if (!to) continue;
                    if (k > f2[to]) k -= f2[to];
                    else {
                        cout << (char) ('a' + i);
                        p = to;
                        break;
                    }
                }
            }
            cout << endl;
        }
    }
}
