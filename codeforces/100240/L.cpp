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

int n;
map<string,int> cnt;
map<string,string> party;
char tmp[1011];

int main() {
    while (scanf("%d\n", &n) == 1) {
        cnt.clear(); party.clear();
        FOR(i,1,n) {
            gets(tmp); string a = string(tmp);
            gets(tmp); string b = string(tmp);
            party[a] = b;
            cnt[a] = 0;
        }
        int q, ln = 0;
        scanf("%d\n", &q);
        while (q--) {
            gets(tmp); string a = string(tmp);
            cnt[a]++;
            ln = max(ln, cnt[a]);
        }
        int has = 0;
        string save = "";
        for(map<string,int> :: iterator it = cnt.begin(); it != cnt.end(); ++it)
            if (it->second == ln) {
                ++has;
                save = it->first;
            }

        if (has > 1) puts("tie");
        else puts(party[save].c_str());
    }
    return 0;
}
