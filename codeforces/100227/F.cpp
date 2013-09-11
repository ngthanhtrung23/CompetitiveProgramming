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

long double f[111][111];
string cell[111];
pair<int,int> move[111];
int m, T;

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    cout << (fixed) << setprecision(4);
    while (ntest--) {
        cin >> m >> T;

        move[0] = move[m+1] = make_pair(0, 0);
        FOR(i,1,m) {
            cin >> cell[i];
            if (cell[i][0] == '+') {
                istringstream ss(cell[i].c_str());
                char t; int u;
                ss >> t >> u;
                move[i] = make_pair(1, u);
            }
            else if (cell[i][0] == '-') {
                istringstream ss(cell[i].c_str());
                char t; int u;
                ss >> t >> u;
                move[i] = make_pair(2, u);
            }
            else if (cell[i][0] == 'L') {
                move[i] = make_pair(3, 0);
            }
            else move[i] = make_pair(0, 0);
        }

        memset(f, 0, sizeof f);
        f[0][0] = 1.0;
        FOR(t,0,T-1) {
            FOR(pos,0,m+1) {
                int to;

                FOR(turn,1,2) {
                    to = pos + turn; if (to > m+1) to = m + 1;
                    if (move[to].first == 1) {
                        to += move[to].second;
                        f[t+1][to] += 0.5 * f[t][pos];
                    }
                    else if (move[to].first == 2) {
                        to -= move[to].second;
                        f[t+1][to] += 0.5 * f[t][pos];
                    }
                    else if (move[to].first == 3) {
                        f[t+2][to] += 0.5 * f[t][pos];
                    }
                    else {
                        f[t+1][to] += 0.5 * f[t][pos];
                    }
                }
            }
        }
        long double res = f[T][m+1];
        if (fabs(res - 0.5) < 1e-9) {
            cout << "Push. 0.5000" << endl;
        }
        else if (res < 0.5) cout << "Bet against. " << res << endl;
        else cout << "Bet for. " << res << endl;
    }
    return 0;
}
