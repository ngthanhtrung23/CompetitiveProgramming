#include <cstdio>
#include <cstring>
#include <algorithm>
#define FOR(i,s,e) for (int i=(s); i<(e); i++)
#define FOE(i,s,e) for (int i=(s); i<=(e); i++)
#define FOD(i,s,e) for (int i=(s)-1; i>=(e); i--)
#define CLR(a,x) memset(a, x, sizeof(a))
#define EXP(i,l) for (int i=(l); i; i=qn[i])
#define N 25
using namespace std;

int n, ok, t, a[N], b[N][N], ret;
char dp[24][1<<23], W[1<<24];

int possible(int lim){
    int ok;
    CLR(dp, 0);
    dp[1][2] = 1;
    if (lim >= 2) dp[1][3] = 1;
    FOR(i,2,n){
        FOR(j,0,1<<i) if (dp[i-1][j]){
            ok = 0;
            FOR(k,0,i) if (b[i][k] != -1 && (j & (1<<k)) && (j & (1<<b[i][k]))) ok = 1;
            if (!ok) continue;
            if (i == n - 1) return 1;
            if (W[j] < lim) dp[i][j | (1<<i)] = 1;
            FOR(k,0,i) if (j & (1<<k)) dp[i][(j & ~(1<<k)) | (1<<i)] = 1;
        }
    }
    return 0;
}

int main(){
    scanf("%d", &n);
    if (n == 1) {
        puts("1");
        return 0;
    }
    FOR(i,0,n) scanf("%d", &a[i+1]);
    ++n;
    FOR(i,2,n){
        ok = 0;
        FOR(j,0,i){
            b[i][j] = -1;
            FOR(k,0,i) if (a[j] + a[k] == a[i]) b[i][j] = k, ok = 1;
        }
        if (!ok){
            puts("-1");
            return 0;
        }
    }
    
    FOR(i,0,1<<n){
        t = i;
        while (t) W[i] += (t & 1), t >>= 1;
    }
    
    for (int i=1, j=16, k; j>=i; ){
        k = (i + j) >> 1;
        if (possible(k)) ret = k, j = k - 1;
        else i = k + 1;
    }
    printf("%d\n", ret);
    return 0;
}