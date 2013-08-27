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

int a, b;
string s;
pair<int,int> pos[1011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a >> b) {
        cin >> s;

        pos[0] = make_pair(0, 0);
        int l = s.length();
        REP(i,l) {
            pos[i+1] = pos[i];
            if (s[i] == 'L') --pos[i+1].first;
            else if (s[i] == 'R') ++pos[i+1].first;
            else if (s[i] == 'U') ++pos[i+1].second;
            else --pos[i+1].second;
        }

        bool ok = false;
        FOR(i,0,l)
            if (pos[i] == make_pair(a, b))
                ok = true;
        if (ok) {
            puts("Yes");
            continue;
        }

        FOR(i,1,l) {
            if (pos[l].first == 0 && pos[l].second == 0) {
            }
            else if (pos[l].first == 0) {
                if (pos[i].first == a && (b - pos[i].second) % pos[l].second == 0
                        && (b - pos[i].second) / pos[l].second >= 0) {
                    ok = true;
                }
            }
            else if (pos[l].second == 0) {
                if (pos[i].second == b && (a - pos[i].first) % pos[l].first == 0
                        && (a - pos[i].first) / pos[l].first >= 0) {
                    ok = true;
                }
            }
            else {
                if ((a - pos[i].first) % pos[l].first == 0
                        && (b - pos[i].second) % pos[l].second == 0) {
                    int k1 = (a - pos[i].first) / pos[l].first;
                    int k2 = (b - pos[i].second) / pos[l].second;
                    if (k1 == k2 && k1 >= 0) {
                        ok = true;
                    }
                }
            }
        }
        if (ok) puts("Yes");
        else puts("No");
    }
    return 0;
}
