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

const int MN = 2011;

int n;
long double r, h;
pair<long double,int> a[3][MN];
int match[2][MN];

long double alpha(long double a, long double b) {
    long double res = fabs(a - b);
    while (res >= 2*M_PI) res -= 2 * M_PI;
    return res;
}

long double get(long double r, long double alpha) {
    return r * min(alpha, 2*M_PI - alpha);
}

#define sqr(x) ((x) * (x))

int main() {
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);

    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(15);

    while (cin >> n >> r >> h) {
        h /= 2.0;
        REP(t,3) {
            FOR(i,1,n) {
                cin >> a[t][i].first;
                a[t][i].second = i;
                if (a[t][i].first < 0) a[t][i].first += 2 * M_PI;
            }
            sort(a[t]+1, a[t]+n+1);
        }

        long double res = 0, best;
        int save1 = -1, save2 = -1;

        // Match top - middle
        best = 1e100;
        FOR(j,1,n) { // top(1) - middle(j)
            long double cur = 0;
            for(int i = 1, u = j; i <= n; ++i, u = (u == n) ? 1 : u+1) {
                cur += sqrt(sqr(h) + sqr(get(r, alpha(a[0][i].first, a[1][u].first))));
            }
            if (cur < best) {
                best = cur;
                save1 = j;
            }
        }
        res += best;
        for(int i = 1, u = save1; i <= n; ++i, u = (u == n) ? 1 : u+1)
            match[0][i] = u;

        // Match middle - base
        best = 1e100;
        FOR(j,1,n) { // middle(1) - base(j)
            long double cur = 0;
            for(int i = 1, u = j; i <= n; ++i, u = (u == n) ? 1 : u+1) {
                cur += sqrt(sqr(h) + sqr(get(r, alpha(a[1][i].first, a[2][u].first))));
            }
            if (cur < best) {
                best = cur;
                save2 = j;
            }
        }
        res += best;
        for(int i = 1, u = save2; i <= n; ++i, u = (u == n) ? 1 : u+1)
            match[1][i] = u;

        cout << res << endl;
        FOR(i,1,n) {
            int j = match[0][i];
            int k = match[1][j];
            cout << a[0][i].second << ' ' << a[1][j].second << ' ' << a[2][k].second << endl;
        }
    }
    return 0;
}
