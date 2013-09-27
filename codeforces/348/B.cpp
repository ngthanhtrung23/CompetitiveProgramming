#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
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

const int MN = 100111;

vector<int> ke[MN];
long long mult[MN], a[MN], sum;
int n, cnt[MN];

long long lcm(long long a, long long b) {
    return a * b / __gcd(a, b);
}

void dfs(int u, int fu) {
    cnt[u] = 0;
    long long l = 1;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        dfs(v, u);
        ++cnt[u];
        l = lcm(l, mult[v]);
        if (l < 0) {
            cout << sum << endl;
            exit(0);
        }
    }

    if (cnt[u] == 0) {
        mult[u] = 1;
    }
    else {
        mult[u] = l * cnt[u];
    }
}

bool check(int u, int fu, long long val) {
    if (cnt[u] == 0) { // leaf
        return a[u] >= val;
    }

    // non-leaf
    long long each = val / cnt[u];
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        if (!check(v, u, each)) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        sum = 0;
        FOR(i,1,n) cin >> a[i], sum += a[i];
        FOR(i,1,n) ke[i].clear();

        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        dfs(1, -1);
        // PR(mult, n);

        long long l = 0, r = 1000111000111000 / mult[1], res = 0;
        while (l <= r) {
            long long mid = (l + r) >> 1;
            if (check(1, -1, mid * mult[1])) {
                l = mid + 1;
                res = mid;
            }
            else r = mid - 1;
        }
        cout << sum - res*mult[1] << endl;
    }
    return 0;
}
