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
const int MN = 100111;

int d[MN], pos[MN], h[MN], t[MN];
long long val[MN], sumVal[MN];
long long f[111][MN];
int m, n, p;
deque<int> q;

long long g(int x, int j, int k) {
    return f[x-1][j] - f[x-1][k] + sumVal[j] - sumVal[k];
}

long long fi(int x, int i, int j) {
    return f[x-1][j] + val[i] * (i-j) - sumVal[i] + sumVal[j];
}

template <typename T> void write(T a) {
    FOR(i,0,a.size()-1) cout<<a[i]<<" ";
    cout<<endl;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &p) == 3) {
        FOR(i,2,n) {
            scanf("%d", &d[i]);
            pos[i] = pos[i-1] + d[i];
        }
        FOR(i,1,m) {
            scanf("%d%d", &h[i], &t[i]);
            val[i] = t[i] - pos[h[i]];
        }
        sort(val+1, val+m+1);
        FOR(i,1,m) sumVal[i] = sumVal[i-1] + val[i];

        if (p >= m) {
            puts("0");
            continue;
        }

        f[0][0] = 0;
        FOR(i,1,m) f[0][i] = 1000111000111000111LL;

        // PR(val, m);

        FOR(x,1,p) {
            // DEBUG(x);
            while (!q.empty()) q.pop_back();

            f[x][x] = 0;
            q.push_back(x-1);

            FOR(i,x+1,m) {
                // DEBUG(i);
                // PR0(q, q.size());

                // if (q.size() > 1) cout << (fixed) << setprecision(6) << g(x, q[1], q[0]) / (long double) (q[1] - q[0]) << ' ' << val[i] << endl;

                while (q.size() > 1 && g(x, q[1], q[0]) <= val[i] * (q[1] - q[0])) q.pop_front();

                // PR0(q, q.size());
                f[x][i] = fi(x, i, q[0]);

                q.PB(i-1);
                while (q.size() > 1
                        && g(x, i, q[q.size()-1]) * (q[q.size()-1] - q[q.size()-2])
                            <= g(x, q[q.size()-1], q[q.size()-2]) * (i - q[q.size()-1]))
                    q.pop_back();

                f[x][i] = min(f[x][i], fi(x, i, i-1));
            }

            // PR(f[x], m);
        }
        cout << f[p][m] << endl;
    }
    return 0;
}
