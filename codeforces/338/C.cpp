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

long long a[11], cnt[11], cur[11], prod[11];
int n, father[11];
long long res;

void attempt(int i) {
    if (i > n) {
        long long t = n;
        FOR(i,2,n)
        if (father[i] == 0) {
            ++t;
            break;
        }

        FOR(i,1,n)
        if (cnt[i] > 1) {
            t += cur[i];
        }

        res = min(res, t);
        return ;
    }

    for(int j = 0; j < i; ++j)
        if (prod[j] % a[i] == 0) {
            father[i] = j;
            prod[j] /= a[i];
            cur[j] -= cnt[i];

            attempt(i+1);

            prod[j] *= a[i];
            cur[j] += cnt[i];
        }
}

int main() {
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1, greater<long long>());

        FOR(i,1,n) {
            cnt[i] = 0;
            long long u = a[i];
            for(long long p = 2; p*p <= a[i]; ++p)
                if (u % p == 0) {
                    while (u % p == 0) {
                        u /= p;
                        ++cnt[i];
                    }
                }
            if (u > 1) ++cnt[i];
        }
        // PR(a, n);
        // PR(cnt, n);

        FOR(i,1,n) {
            cur[i] = cnt[i];
            prod[i] = a[i];
        }

        res = 1000111000111000111LL;
        attempt(1);
        cout << res << endl;
    }
    return 0;
}