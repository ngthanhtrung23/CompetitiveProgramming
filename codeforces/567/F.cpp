
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

const int UNKNOWN = 0;
const int EQUAL = 3;
const int LEQ = -1;
const int LESS = -2;
const int GEQ = 1;
const int GREATER = 2;

const int MN = 211;
int n, k;
int relations[MN][MN];

ll f[MN][MN];
bool contradict;

void addRequirement(int u, int v, string rel) {
    if (rel == ">") {
        addRequirement(v, u, "<");
        return ;
    }
    if (rel == ">=") {
        addRequirement(v, u, "<=");
        return ;
    }
    if (u == v) {
        if (rel == "<") contradict = true;
    }

    if (rel == "=") {
        if (relations[u][v] == LESS || relations[u][v] == GREATER) contradict = true;

        relations[u][v] = relations[v][u] = EQUAL;
    }
    else if (rel == "<") {
        if (relations[u][v] == EQUAL || relations[u][v] == GREATER || relations[u][v] == GEQ) contradict = true;

        relations[u][v] = LESS;
        relations[v][u] = GREATER;
    }
    else {
        assert(rel == "<=");

        if (relations[u][v] == EQUAL || relations[u][v] == LESS) return;

        if (relations[u][v] == GEQ) {
            relations[u][v] = relations[v][u] = EQUAL;
            return ;
        }

        if (relations[u][v] == GREATER) {
            contradict = true;
            return ;
        }

        relations[u][v] = LEQ;
        relations[v][u] = GEQ;
    }
}

void input() {
    memset(relations, UNKNOWN, sizeof relations);
    FOR(i,1,n+n) relations[i][i] = EQUAL;

    FOR(i,1,k) {
        int u, v;
        string rel;
        cin >> u >> rel >> v;
        addRequirement(u, v, rel);
    }
}

bool check(int x, int y, int from, int to) {
    FOR(i,1,n+n)
        if (i != y && i != x && relations[x][i] != UNKNOWN) {
            if (relations[x][i] == EQUAL) return false;
            if (relations[x][i] == LESS || relations[x][i] == LEQ) {
                // x <= i
                if (from <= i && i <= to) {
                }
                else return false;
            }
            
            if (relations[x][i] == GEQ || relations[x][i] == GREATER) {
                // x >= i
                if (from <= i && i <= to) return false;
            }
        }
    return true;
}

bool can(int x, int y, int from, int to) {
    if (relations[x][y] == LESS || relations[x][y] == GREATER) return false;

    return check(x, y, from, to) && check(y, x, from, to);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        contradict = false;
        input();
        if (contradict) {
            cout << 0 << endl;
            continue;
        }
        memset(f, 0, sizeof f);
        f[0][n+n+1] = 1;
        FOR(i,0,n+n+1) FORD(j,n+n+1,i+5) if (f[i][j]) {
            // 3 cases:
            // (i+1) (i+2)
            if (can(i+1, i+2, i+3, j-1)) {
                f[i+2][j] += f[i][j];
            }
            // (j-2) (j-1)
            if (can(j-2, j-1, i+1, j-3)) {
                f[i][j-2] += f[i][j];
            }
            // (i+1) (j-1)
            if (can(i+1, j-1, i+2, j-2)) {
                f[i+1][j-1] += f[i][j];
            }
        }

        ll res = 0;
        FOR(i,1,n+n-1) if (can(i, i+1, -1, -1)) {
            res += f[i-1][i+2];
        }
        cout << res << endl;
    }
}

