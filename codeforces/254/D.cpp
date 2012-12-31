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

int m, n, k;
char a[1011][1011];
pair<int,int> qu[1011 * 1011], ls1[10111], ls2[10111];
int d[1011][1011];
bool c[1011][1011];
int first, last, sz1, sz2;
vector<pair<int,int> > found;

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

void bfs(int startu, int startv) {
    first = last = 1;
    d[startu][startv] = 0;
    qu[1] = MP(startu, startv);

    while (first <= last) {
        pair<int,int> u = qu[first++];
        if (d[u.F][u.S] == k) continue;

        REP(dir,4) {
            pair<int,int> v = MP(u.F + di[dir], u.S + dj[dir]);

            if (v.F < 1 || v.F > m || v.S < 1 || v.S > n) continue;
            if (a[v.F][v.S] == 'X') continue;

            if (d[v.F][v.S] < 0) {
                d[v.F][v.S] = d[u.F][u.S] + 1;
                qu[++last] = v;
            }
        }
    }
}

void resetD() {
    FOR(i,1,last) {
        pair<int,int> u = qu[i];
        d[u.F][u.S] = -1;
    }
}

vector< pair<int,int> > rats, caught;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (scanf("%d%d%d\n", &m, &n, &k) == 3) {
        memset(d, -1, sizeof d);

        FOR(i,1,m) scanf("%s\n", &a[i][1]);

        bool found = false;
        int fi, fj, cntRat = 0;
        rats.clear();

        FOR(i,1,m) FOR(j,1,n) {
            if (a[i][j] == 'R') {
                ++cntRat;
                rats.PB(MP(i,j));
                if (!found) {
                    fi = i; fj = j;
                    found = true;
                }
            }
        }

        bfs(fi, fj);

        sz1 = last;
        FOR(i,1,sz1) ls1[i] = qu[i];

        resetD();

        pair<int,int> pos1, pos2;
        bool solution = false;

        FOR(t,1,sz1) {
            bfs(ls1[t].F, ls1[t].S);

            bool found = false;

            int done = 0;

            REP(i,caught.size()) {
                pair<int,int> u = caught[i];
                c[u.F][u.S] = false;
            }
            caught.clear();
            FOR(i,1,last) {
                pair<int,int> u = qu[i];
                if (a[u.F][u.S] == 'R') {
                    c[u.F][u.S] = true;
                    caught.PB(u);
                    ++done;
                }
            }

            if (done < cntRat) {
                REP(i,cntRat)
                    if (c[rats[i].F][rats[i].S] == false) {
                        fi = rats[i].F;
                        fj = rats[i].S;
                        found = true;
                        break;
                    }
            }

            if (!found) {
                solution = true;
                pos1 = ls1[t];

                found = false;
                FOR(i,1,m) FOR(j,1,n) if (!found)
                if (a[i][j] != 'X' && MP(i,j) != pos1) {
                    found = true;
                    pos2 = MP(i,j);
                    break;
                }
                break;
            }
            else {
                resetD();

                bfs(fi, fj);
                sz2 = last;
                FOR(i,1,sz2) ls2[i] = qu[i];
                resetD();

                FOR(x,1,sz2) {
                    bfs(ls2[x].F, ls2[x].S);

                    bool found = false;
                    REP(i,rats.size()) {
                        pair<int,int> u = rats[i];
                        if (d[u.F][u.S] < 0 && !c[u.F][u.S]) {
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        solution = true;
                        pos1 = ls1[t]; pos2 = ls2[x];
                        break;
                    }

                    resetD();
                }
            }
            if (solution) break;
        }

        if (!solution) {
            puts("-1");
        }
        else cout << pos1.F << ' ' << pos1.S << ' ' << pos2.F << ' ' << pos2.S << endl;
    }
    return 0;
}
