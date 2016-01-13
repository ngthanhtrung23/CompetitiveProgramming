#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
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

const int MN = 1000 * 1000;
int a[MN + 11], id[MN + 11];
bool used[MN + 11], sieve[MN + 11];
vector<int> uoc[MN + 11];
int run[MN + 11];

int main() {
    // freopen("input.txt", "r", stdin);
    ios :: sync_with_stdio(false);
    FOR(i,2,MN) if (!sieve[i]) {
        uoc[i].push_back(i);
        for(int j = i+i; j <= MN; j += i) {
            sieve[j] = true;
            uoc[j].push_back(i);
        }
    }

    int cur = 2;
    a[1] = 1; id[1] = 1;
    a[2] = 2; id[2] = 2;

    run[2] = 2;
    int diff = 2;

    used[1] = used[2] = true;

    int cnt = 2;
    FOR(i,3,650000) {
        int nextdiff = diff;
        int res = a[i-1] + diff;
        while (res <= MN && used[res]) {
            res += diff;
        }

        REP(t,uoc[a[i-1]].size()) {
            int u = uoc[a[i-1]][t];
            if (run[u] < a[i-1]) {
                int add = run[u] + u;
                while (add <= MN && used[add]) run[u] += u, add += u;

                if (add < res) {
                    res = add;
                    nextdiff = u;
                }
            }
        }

        diff = nextdiff;
        a[i] = res; id[res] = i; used[res] = true;
        run[diff] = res;
        if (res <= 300000) {
            ++cnt;
            if (cnt == 300000) break;
        }
    }
    // DEBUG(cnt);

    int n; while (cin >> n && n) printf("The number %d appears in location %d.\n", n, id[n]);

    return 0;
}