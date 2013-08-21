#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define REP2(i,a) for(i=0; i<a; i++)
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

int team[11], a, b, c;
bool good[11][11];
string u, v;

int conv(string name) {
    if (name == "Anka") return 0;
    else if (name == "Chapay") return 1;
    else if (name == "Cleo") return 2;
    else if (name == "Troll") return 3;
    else if (name == "Dracul") return 4;
    else if (name == "Snowy") return 5;
    else if (name == "Hexadecimal") return 6;

    cout << "???\n";
}

int main() {
    int m;
    while (cin >> m) {
        memset(good, false, sizeof good);
        while (m--) {
            cin >> u >> v; cin >> v;
            good[conv(u)][conv(v)] = true;
        }
        cin >> a >> b >> c;

        int res1 = 2000111000, res2 = 0;

        REP2(team[0],3)
        REP2(team[1],3)
        REP2(team[2],3)
        REP2(team[3],3)
        REP2(team[4],3)
        REP2(team[5],3)
        REP2(team[6],3) {
            int cnt[3]; cnt[0] = cnt[1] = cnt[2] = 0;
            REP(i,7) cnt[team[i]]++;

            if (!cnt[0] || !cnt[1] || !cnt[2]) continue;

            int x = a / cnt[0], y = b / cnt[1], z = c / cnt[2];
            int nn = min(min(x, y), z);
            int ln = max(max(x, y), z);

            int now1 = ln - nn, now2 = 0;
            REP(i,7) REP(j,7) if (i != j)
                if (good[i][j] && team[i] == team[j])
                    ++now2;

            if (now1 < res1) {
                res1 = now1;
                res2 = now2;
            }
            else if (now1 == res1) {
                res2 = max(res2, now2);
            }
        }
        cout << res1 << ' ' << res2 << endl;
    }
    return 0;
}
