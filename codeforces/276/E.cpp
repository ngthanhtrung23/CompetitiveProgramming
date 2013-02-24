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
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

const long double PI = acos((long double) -1.0);

const int MN = 100111;

int n, q, height[MN], chainID[MN], posID[MN], nChain;
long long add[MN * 6];
vector<int> chain[MN], ke[MN];
vector<long long> value[MN];

void init() {
    nChain = 0;
    memset(height, 0, sizeof height);
    memset(add, 0, sizeof add);
    memset(chainID, 0, sizeof chainID);
    memset(posID, 0, sizeof posID);
    FOR(i,1,n) {
        chain[i].clear();
        ke[i].clear();
        value[i].clear();
    }
}

void dfs(int u, int fu) {
    chain[nChain].PB(u);
    chainID[u] = nChain;
    posID[u] = chain[nChain].size()-1;
    height[u] = height[fu] + 1;

    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        dfs(v, u);
    }
}

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void updateValue(int c, int i, int l, int r, int u, int v, int k) {
    if (v < u) return ;
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        value[c][i] += k;
        return ;
    }
    int mid = (l + r) >> 1;
    updateValue(c, CT(i), l, mid, u, v, k);
    updateValue(c, CP(i), mid+1, r, u, v, k);
}

void updateAdd(int i, int l, int r, int u, int v, int k) {
    if (v < u) return ;
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        add[i] += k;
        return ;
    }
    int mid = (l + r) >> 1;
    updateAdd(CT(i), l, mid, u, v, k);
    updateAdd(CP(i), mid+1, r, u, v, k);
}

long long getValue(int c, int i, int l, int r, int u) {
    if (u < l || r < u) return 0;
    if (l == r) return value[c][i];

    int mid = (l + r) >> 1;
    return value[c][i] + getValue(c, CT(i), l, mid, u) + getValue(c, CP(i), mid+1, r, u);
}

long long getAdd(int i, int l, int r, int u) {
    if (u < l || r < u) return 0;
    if (l == r) return add[i];

    int mid = (l + r) >> 1;
    return add[i] + getAdd(CT(i), l, mid, u) + getAdd(CP(i), mid+1, r, u);
}

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        init();
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].PB(v); ke[v].PB(u);
        }

        height[1] = 1;
        REP(i,ke[1].size()) {
            int u = ke[1][i];
            ++nChain;
            chain[nChain].PB(-1);
            chain[nChain].PB(1);
            dfs(u, 1);

            value[nChain].resize(chain[nChain].size() * 6);
        }

        // DEBUG(nChain);
        // PR(chainID, n);
        // PR(posID, n);
        // FOR(i,1,nChain) {
        //     PR0(chain[i], chain[i].size());
        // }

        while (q--) {
            int yc;
            scanf("%d", &yc);
            if (yc == 0) {
                int v, x, d;
                scanf("%d%d%d", &v, &x, &d);

                if (v == 1) {
                    updateAdd(1, 1, n, 1, d+1, x);
                    // cout << "Add: " << 1 << ' ' << d+1 << ' ' << x << endl << endl;
                }
                else {
                    int c = chainID[v];
                    int p = posID[v];

                    // Go down
                    updateValue(c, 1, 1, chain[c].size()-1, p, p+d, x);
                    // cout << "Value: " << c << ' ' << p << ' ' << p+d << ' ' << x << endl;

                    // Go up
                    if (p - d >= 1) {
                        updateValue(c, 1, 1, chain[c].size()-1, p-d, p-1, x);
                        // cout << "Value: " << c << ' ' << p-d << ' ' << p-1 << ' ' << x << endl;
                        if (p-d <= 1)
                            updateAdd(1, 1, n, 1, 1, x);
                    }
                    else {
                        int can = d - p + 1;
                        updateAdd(1, 1, n, 1, can+1, x);
                        if (can + 1 >= p)
                            updateValue(c, 1, 1, chain[c].size()-1, p, min(can+1, p+d), -x);
                        else
                            updateValue(c, 1, 1, chain[c].size()-1, can+2, p-1, x);

                        // cout << "Add: " << 1 << ' ' << can+1 << ' ' << x << endl;
                        // cout << "Value: " << c << ' ' << p << ' ' << p << ' ' << -x << endl;
                    }
                    // cout << endl;
                }
            }
            else {
                int v; scanf("%d", &v);
                int c = chainID[v];
                int p = posID[v];
                if (v == 1) {
                    printf("%d\n", (int) getAdd(1, 1, n, 1));
                }
                else {
                    printf("%d\n", (int) (
                        getValue(c, 1, 1, chain[c].size()-1, p) + 
                        getAdd(1, 1, n, height[v])));
                }
            }

            // cout << "Now\n";
            // FOR(i,1,n) cout << getAdd(1,1,n,i) << ' '; cout << endl;
            // FOR(c,1,nChain) {
            //     FOR(i,1,chain[c].size()-1)
            //         cout << getValue(c,1,1,chain[c].size()-1,i) << ' ';
            //     cout << endl;
            // }
        }
    }
    return 0;
}
