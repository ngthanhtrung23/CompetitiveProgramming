#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=a; i<=b; i++)
#define REP(i,a) for(int i = 0; i < a; i++)
using namespace std;

int g[611][611],dd[611*611];

void gen() {
    int k = 0;
    FOR(u, 1, 512) {
        if (u%10 == 0) cerr<<u<<endl;
        FOR(v,1,512) {
            k++;
            FOR(i,0,u-1)
            FOR(j,0,v-1)
                dd[g[i][j]^g[i][v]^g[u][j]]=k;
                
            int res=0;
            while (dd[res]==k) res++;
            g[u][v]=res;
        }
    }
    
    FOR(u,0,9) {
        FOR(v,0,9) printf("%6d, ",g[1<<u][1<<v]);
        cout<<endl;
    }
}

const int g1[10][10] = 
{{    1,      2,      4,      8,     16,     32,     64,    128,    256,    512}, 
{     2,      3,      8,     12,     32,     48,    128,    192,    512,    768}, 
{     4,      8,      6,     11,     64,    128,     96,    176,   1024,   2048}, 
{     8,     12,     11,     13,    128,    192,    176,    208,   2048,   3072}, 
{    16,     32,     64,    128,     24,     44,     75,    141,   4096,   8192}, 
{    32,     48,    128,    192,     44,     52,    141,    198,   8192,  12288}, 
{    64,    128,     96,    176,     75,    141,    103,    185,  16384,  32768}, 
{   128,    192,    176,    208,    141,    198,    185,    222,  32768,  49152}, 
{   256,    512,   1024,   2048,   4096,   8192,  16384,  32768,    384,    704}, 
{   512,    768,   2048,   3072,   8192,  12288,  32768,  49152,    704,    832}}; 

int get(int u, int v) {
    int res = 0;
    REP(i,10)
    REP(j,10)
        if (u & (1<<i))
        if (v & (1<<j))
            res ^= g1[i][j];
    return res;
}

char a[111][111];

int main() {
    freopen("coins.in","r",stdin);
    freopen("coins.out","w",stdout);
    int m, n;
    while (cin >> m >> n) {
        int sum = 0;
        FOR(i,1,m) FOR(j,1,n) {
            char c; cin >> c;
            a[i][j] = c;
            if (c == '1') sum ^= get(i, j);
        }
        if (sum) {
            cout << "Ann" << endl;
            try {
                FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '1') {
                    FOR(u,0,i-1) FOR(v,0,j-1) {
                        if ((sum ^ get(i, j) ^ get(u, v) ^ get(i, v) ^ get(u, j)) == 0) {
                            cout << i << ' ' << j << endl;
                            cout << u << ' ' << v << endl;
                            throw 1;
                        }
                    }
                }
            } catch (int e) {
            }
        }
        else {
            cout << "Betty" << endl;
        }
    }
    return 0;
}
