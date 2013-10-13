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

int n, digit[22];
bool can[22][22];
int save[22][22][10];
int cur[10];

bool f[22][22];
int tru[22][22], tradd[22][22], trrem[22][22];

long long res[11];

void trace(int u, int rem) {
    if (u == 0) return ;

    int curadd = tradd[u][rem], currem = trrem[u][rem];

    FOR(i,1,6) {
        res[i] = (res[i] * 10 + save[curadd][currem][i]);
    }

    trace(u-1, tru[u][rem]);
}

void solve(long long t) {
    n = 0;
    while (t) {
        digit[++n] = t % 10;
        t /= 10;
    }
    // PR(digit, n);
    memset(f, false, sizeof f);
    f[0][0] = true;

    FOR(l,0,n-1) FOR(rem,0,6) if (f[l][rem]) {
        FOR(add,0,9) if ((add+rem) % 10 == digit[l+1]) {
            FOR(newrem,0,6) if (can[add][newrem]) {
                int next = (add + rem) / 10 + newrem;
                f[l+1][next] = true;

                tru[l+1][next] = rem;
                tradd[l+1][next] = add;
                trrem[l+1][next] = newrem;
            }
        }
    }

    if (!f[n][0]) {
        cout << -1 << endl;
    }
    else {
        memset(res, 0, sizeof res);
        trace(n, 0);
        FOR(i,1,6) cout << res[i] << ' '; cout << endl;
    }
}

void attempt(int i, int sum) {
    if (i == 7) {
        if (!can[sum%10][sum/10]) {
            can[sum%10][sum/10] = true;
            FOR(x,1,6) save[sum%10][sum/10][x] = cur[x];
        }
        return ;
    }

    cur[i] = 0;
    attempt(i+1, sum);
    cur[i] = 4;
    attempt(i+1, sum+4);
    cur[i] = 7;
    attempt(i+1, sum+7);
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;

    memset(can, false, sizeof can);
    can[0][0] = true;
    attempt(1, 0);

    while (ntest--) {
        long long t; cin >> t;
        solve(t);
    }
    return 0;
}
