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

const int g[] = {
0,1,1,2,0,3,1,1,0,3,3,2,2,4,0,5,2,2,3,3,0,1,1,3,0,2,1,1,0,4,5,2,7,4,
0,1,1,2,0,3,1,1,0,3,3,2,2,4,4,5,5,2,3,3,0,1,1,3,0,2,1,1,0,4,5,3,7,4,
8,1,1,2,0,3,1,1,0,3,3,2,2,4,4,5,5,9,3,3,0,1,1,3,0,2,1,1,0,4,5,3,7,4,8
};

int grundy(int n) {
    if (n <= 102) return g[n];
    else {
        n = n % 34 + 68;
        return g[n];
    }
}

char s[5011];
int a[5011], l[5011], nl, first[5011], last[5011];

int main() {
    while (gets(s)) {
        int n = strlen(s);
        FOR(i,1,n) {
            if (i > 1 && i < n && s[i-2] == s[i]) a[i] = 1;
            else a[i] = 0;
        }
        // PR(a, n);
        int i = 1, sum = 0;
        nl = 0;

        while (i <= n) {
            if (a[i] == 0) ++i;
            else {
                int j = i;
                while (j < n && a[j+1] == 1) ++j;
                ++nl;
                l[nl] = j - i + 1;
                first[nl] = i;
                last[nl] = j;

                sum ^= grundy(l[nl]);

                i = j + 1;
            }
        }
        // PR(l, nl);
        if (sum) {
            puts("First");
            bool found = false;
            FOR(i,1,nl) {
                FOR(x,first[i],last[i]) {
                    int newSum = sum ^ grundy(l[i]);

                    int left = (x-2) - first[i] + 1;
                    int right = last[i] - (x+2) + 1;

                    if (left > 0) newSum ^= grundy(left);
                    if (right > 0) newSum ^= grundy(right);

                    if (newSum == 0) {
                        found = true;
                        printf("%d\n", x);
                        break;
                    }
                }
                if (found) break;
            }
        }
        else puts("Second");
    }
    return 0;
}
