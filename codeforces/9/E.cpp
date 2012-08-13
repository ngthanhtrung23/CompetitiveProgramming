#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);
const int MN = 55;

int lab[MN], n, m, qu[MN];
pair<int,int> e[MN*MN];
vector<int> ke[MN];
bool mark[MN];
vector< pair<int,int> > ls;
vector<int> zero;

bool check() {
    FOR(i,1,n) ke[i].clear();
    FOR(i,1,m) {
        ke[e[i].F].PB(e[i].S);
        ke[e[i].S].PB(e[i].F);
    }
    if (m != n) return false;

    memset(mark, false, sizeof mark);
    int first = 1, last = 1; qu[1] = 1;
    mark[1] = true;
    while (first <= last) {
        int u = qu[first++];
        REP(i,ke[u].size()) {
            int v = ke[u][i];
            if (mark[v]) continue;

            qu[++last] = v;
            mark[v] = true;
        }
    }
    if (last != n) return false;

    FOR(i,1,n) if (ke[i].size() != 2) return false;
    return true;
}

int getRoot(int u) {
    if (lab[u] < 0) return u;
    else return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[u] = x;
        lab[v] = u;
    }
    else {
        lab[v] = x;
        lab[u] = v;
    }
}

vector< pair<int,int> > res;
int deg[MN];

bool can() {
    if (check()) return true;
    bool ok = true;
    memset(deg, 0, sizeof deg);
    memset(lab, -1, sizeof lab);

    FOR(i,1,m) {
        int u = e[i].F, v = e[i].S;
        ++deg[u]; ++deg[v];

        u = getRoot(u);
        v = getRoot(v);
        if (u == v) {
            ok = false;
            break;
        }
        merge(u, v);
    }
    FOR(i,1,n) if (deg[i] > 2) {
        ok = false;
        break;
    }
    return ok;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        if (n == 1 && m == 0) {
            puts("YES");
            puts("1");
            puts("1 1");
            continue;
        }
        res.clear();
        FOR(i,1,n) {
            ke[i].clear();
        }
        FOR(i,1,m) {
            scanf("%d%d", &e[i].F, &e[i].S);
        }
        if (check()) {
            puts("YES");
            puts("0");
            continue;
        }

        if (!can()) {
            puts("NO");
            continue;
        }


        puts("YES");
        printf("%d\n", n-m);
        int need = n - m;
        FOR(turn,1,need) {
            bool ok = false;
            FOR(u,1,n) {
                FOR(v,u+1,n) {
                    ++m;
                    e[m] = MP(u,v);
                    if (can()) {
                        ok = true;
                        break;
                    }
                    else --m;
                }
                if (ok) break;
            }
            printf("%d %d\n", e[m].F, e[m].S);
        }
    }
    return 0;
}
