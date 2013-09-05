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

bool need[1011];
char s[100111];

int main() {
    while (gets(s)) {
        REP(i,strlen(s)) if (s[i] == ',') s[i] = ' ';
        istringstream ss(s);
        memset(need, false, sizeof need);
        int u; while (ss >> u) need[u] = true;

        int i = 1;
        vector< pair<int,int> > res;
        while (i <= 1000) {
            if (!need[i]) {
                ++i;
            }
            else {
                int j = i;
                while (need[j+1]) ++j;
                res.push_back(make_pair(i, j));
                i = j + 1;
            }
        }
        REP(i,res.size()-1) {
            if (res[i].first == res[i].second) printf("%d,", res[i].first);
            else printf("%d-%d,", res[i].first, res[i].second);
        }
        i = res.size()-1;
        if (res[i].first == res[i].second) printf("%d\n", res[i].first);
        else printf("%d-%d\n", res[i].first, res[i].second);
    }
    return 0;
}
