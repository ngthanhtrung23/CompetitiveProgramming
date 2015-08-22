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

const long long MOD = 1000000009LL;

long long power(long long x, long long k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;

    long long mid = power(x, k >> 1);
    mid = mid * mid % MOD;
    if (k & 1) return mid * x % MOD;
    else return mid;
}

int main() {
    ios :: sync_with_stdio(false);
    long long all, correct, k;
    while (cin >> all >> correct >> k) {
        long long wrong = all - correct;

        long long nGroup = correct / (k-1);
        if (correct % (k-1)) ++nGroup;

        if (wrong >= nGroup-1) {
            cout << correct << endl;
        }
        else {
            long long left = 0, right = nGroup, res = nGroup;
            while (left <= right) {
                long long mid = (left + right) >> 1;

                long long nGroup = (correct - mid*k) / (k-1);
                if ((correct - mid*k) % (k-1)) ++nGroup;
                if (wrong >= nGroup - 1) {
                    res = mid;
                    right = mid - 1;
                }
                else left = mid + 1;
            }

            long long mult = (power(2, res+1) - 2 + MOD) % MOD;

            cout << ((mult * k) + (correct - res * k)) % MOD << endl;
        }
    }
    return 0;
}