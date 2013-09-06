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

struct Problem {
    int I, A, L, O;
} problems[111];

struct Team {
    int T, Z, V, C;
} teams[111];

struct Result {
    int id, ac, penalty;
} res[111];

bool operator < (const Result &a, const Result &b) {
    if (a.ac != b.ac) return a.ac > b.ac;
    if (a.penalty != b.penalty) return a.penalty < b.penalty;
    return a.id < b.id;
}

int m, n, t, l;
pair<int,int> selections[111];

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))
;

inline int up(int a, int b) {
    int res = a / b;
    if (a % b) ++res;
    return res;
}

int main() {
    freopen("unfair.in", "r", stdin);
    freopen("unfair.out", "w", stdout);
    ios :: sync_with_stdio(false);

    while (cin >> m >> n >> t >> l) {
        FOR(i,1,m) cin >> problems[i].I >> problems[i].A >> problems[i].L >> problems[i].O;
        FOR(i,1,t) cin >> teams[i].T >> teams[i].Z >> teams[i].V >> teams[i].C;

        int best = t+1, save = -1;
        REP(mask,TWO(m)) if (__builtin_popcount(mask) == n) {
            // Calculate rank table
            FOR(j,1,t) {
                res[j].id = j;

                int cur = 0;
                FOR(i,1,m) if (CONTAIN(mask,i-1))
                if (teams[j].T + teams[j].C > problems[i].I - problems[i].O) {
                    ++cur;
                    int expected = up(problems[i].I, problems[i].O)
                                + max(up(problems[i].A, teams[j].C), 5);
                    int actual = max(problems[i].I - teams[j].T, 0)
                                + up(problems[i].A, teams[j].Z + teams[j].C)
                                + up(problems[i].L, teams[j].V);
                    selections[cur] = make_pair(expected, actual);
                }

                sort(selections+1, selections+cur+1);
                int used_time = 0;

                res[j].penalty = 0;
                res[j].ac = 0;

                FOR(i,1,cur)
                if (used_time + selections[i].second <= l) {
                    used_time += selections[i].second;

                    res[j].ac++;
                    res[j].penalty += used_time;
                }
                else break;
            }
            sort(res+1, res+t+1);

            int cur = 0;
            FOR(i,1,t) if (res[i].id == 1) cur = i;

            if (cur < best) {
                best = cur;
                save = mask;
            }
        }

        FOR(i,1,m) if (CONTAIN(save,i-1)) cout << i << ' ';
        cout << endl;
    }
    return 0;
}
