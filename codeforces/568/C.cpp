
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 511;

struct Rule {
    int p1, t1, p2, t2;
} rules[1000111];

#define next next___
int typ[MN], next[2][311];
int bound[MN], res[MN];
int nPos, k, nRule;
string tmp;

vector < vector<int> > g, gt;
vector<bool> used;
vector<int> order, comp;

void dfs1 (int v) {
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs1 (to);
        }
        order.push_back (v);
}
void dfs2 (int v, int cl) {
    comp[v] = cl;
    for (size_t i=0; i<gt[v].size(); ++i) {
        int to = gt[v][i];
        if (comp[to] == -1)
            dfs2 (to, cl);
        }
}

void addEdge(int u, int v) {
    g[u].push_back(v);
    gt[v].push_back(u);
}

void removeEdge(int u, int v) {
    g[u].pop_back();
    gt[v].pop_back();
}

void init() {
    int n = 2*nPos;
    g.resize(n);
    gt.resize(n);
    REP(i,n) {
        g[i].clear();
        gt[i].clear();
    }
    FOR(i,1,nRule) {
        addEdge(rules[i].p1*2+rules[i].t1, rules[i].p2*2+rules[i].t2);
        addEdge(rules[i].p2*2+1-rules[i].t2, rules[i].p1*2+1-rules[i].t1);
    }
}

bool check(int pos) {
    int n = 2*nPos;
    used.clear();
    order.clear();
    comp.clear();

//    DEBUG(pos);
//    PR0(res, nPos);
//    PR0(bound, nPos);
    FOR(i,0,pos) {
        addEdge(2*i+1-typ[res[i]], 2*i+typ[res[i]]);
    }
    FOR(i,pos+1,nPos-1) {
        int cur = 0;
        if (next[0][cur] < 0) {
            addEdge(2*i+0, 2*i+1);
        }
        if (next[1][cur] < 0) {
            addEdge(2*i+1, 2*i+0);
        }
    }

    used.assign (n, false);
    REP(i,n)
        if (!used[i])    dfs1 (i);
    comp.assign (n, -1);
    for (int i=0, j=0; i<n; ++i) {
        int v = order[n-i-1];
        if (comp[v] == -1) dfs2 (v, j++);
    }

    FOR(i,0,pos) {
        removeEdge(2*i+1-typ[res[i]], 2*i+typ[res[i]]);
    }
    FOR(i,pos+1,nPos-1) {
        int cur = 0;
        if (next[0][cur] < 0) {
            removeEdge(2*i+0, 2*i+1);
        }
        if (next[1][cur] < 0) {
            removeEdge(2*i+1, 2*i+0);
        }
    }

    REP(i,n)
        if (comp[i] == comp[i^1]) {
//            cout << ":@)\n";
            return false;
        }
//    cout << ":3\n";
    for (int i=0; i<n; i += 2) {
        int ans = comp[i] > comp[i^1] ? 0 : 1;
        
        if (i/2 > pos) {
            res[i/2] = next[ans][0];
        }
    }
    return true;
}

void finish(int start) {
    FOR(i,start,nPos-1) {
        int cur0 = next[0][0];
        int cur1 = next[1][0];
        if (cur0 > cur1) swap(cur0, cur1);

        if (cur0 >= 0) {
            res[i] = cur0;
            if (check(i)) continue;
        }
        res[i] = cur1;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> tmp) {
        k = tmp.length();
        REP(i,k) typ[i] = (tmp[i] == 'V') ? 0 : 1;
        cin >> nPos >> nRule;
        FOR(i,1,nRule) {
            char x1, x2;
            cin >> rules[i].p1 >> x1 >> rules[i].p2 >> x2;

            --rules[i].p1;
            --rules[i].p2;

            rules[i].t1 = (x1 == 'V') ? 0 : 1;
            rules[i].t2 = (x2 == 'V') ? 0 : 1;
        }
        cin >> tmp;
        nPos = tmp.length();
        REP(i,nPos) {
            bound[i] = tmp[i] - 'a';
        }

//        PR0(typ, k);
//        PR0(bound, nPos);

        REP(i,k) {
            next[0][i] = next[1][i] = -1;
            FOR(c,i,k-1) {
                REP(val,2)
                    if (next[val][i] < 0 && typ[c] == val)
                        next[val][i] = c;
            }
//            cout << next[0][i] << ' ' << next[1][i] << endl;
        }
        try {
            init();
            bool found = false;
            FORD(same,nPos-1,-1) {
                FOR(i,0,same) res[i] = bound[i];
                if (same == nPos-1) {
                    if (check(same)) {
                        found = true;
                        break;
                    }
                }
                else {
                    int d = bound[same+1];
                    if (d != k-1) {
                        int cur0 = next[0][d+1];
                        int cur1 = next[1][d+1];

                        if (cur0 > cur1) swap(cur0, cur1);
                        if (cur0 >= 0) {
                            res[same+1] = cur0;
                            if (check(same+1)) {
                                finish(same+2);
                                found = true;
                                break;
                            }
                        }
                        if (cur1 >= 0) {
                            res[same+1] = cur1;
                            if (check(same+1)) {
                                finish(same+2);
                                found = true;
                                break;
                            }
                        }
                    }
                    if (found) break;
                }
            }
            if (!found) throw 1;
            REP(i,nPos) {
                cout << (char) (res[i] + 'a');
            }
            cout << endl;
        } catch (...) {
            cout << -1 << endl;
        }
    }
}

