#include <bits/stdc++.h>

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

const long double PI = acos((long double) -1.0);
const int MN = 50111;

char s[MN];
int n, f[MN][111], next[MN][33];
pair<int,int> trace[MN][111];

void print(int i, int l) {
    if (l == 0) return ;
    if (l == 1) {
        putchar(s[i]);
        return ;
    }

    putchar(s[trace[i][l].first]);
    print(trace[i][l].first+1, l-2);
    putchar(s[trace[i][l].second]);
}

int main() {
    while (gets(s)) {
        n = strlen(s);
        FORD(i,n,0) {
            FOR(c,'a','z') {
                next[i][c-'a'] = (i == n) ? n : next[i+1][c-'a'];
            }
            next[i][s[i]-'a'] = i;
        }
        FORD(i,n,0) {
            f[i][1] = i;
            trace[i][1] = make_pair(i, i);

            if (i >= n-1) {
                f[i][2] = n;
                continue;
            }

            f[i][2] = f[i+1][2];
            trace[i][2] = trace[i+1][2];

            int j = next[i+1][s[i]-'a'];
            if (j < f[i][2]) {
                f[i][2] = j;
                trace[i][2] = make_pair(i, j);
            }
        }

        FOR(l,3,100) {
            f[n][l] = n;
            FORD(i,n-1,0) {
                f[i][l] = f[i+1][l];
                trace[i][l] = trace[i+1][l];

                if (i+1 < n) {
                    int j = f[i+1][l-2];
                    if (j >= n-1) continue;

                    int last = next[j+1][s[i]-'a'];

                    if (last < f[i][l]) {
                        f[i][l] = last;
                        trace[i][l] = make_pair(i, last);
                    }
                }
            }
        }

        FORD(l,100,1) {
            if (f[0][l] < n) {
                print(0, l);
                puts("");
                break;
            }
        }
    }
    return 0;
}
