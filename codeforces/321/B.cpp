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

int a[111], b[111], x[111], na, nb, n;

int main() {
    ios :: sync_with_stdio(false);
    int m;
    while (cin >> m >> n) {
        na = nb = 0;
        FOR(i,1,m) {
            string tmp; cin >> tmp;
            if (tmp == "ATK") cin >> a[++na];
            else cin >> b[++nb];
        }
        FOR(i,1,n) cin >> x[i];

        // PR(a, na);
        // PR(b, nb);
        // PR(x, n);

        int best = 0;

        // kill them all!!!
        if (n >= na + nb) {
            multiset<int> s;
            FOR(i,1,n) s.insert(x[i]);

            bool can = true;
            int res = 0;
            FOR(i,1,nb) {
                __typeof(s.begin()) it = s.upper_bound(b[i]);
                if (it == s.end()) {
                    can = false;
                    break;
                }
                else {
                    s.erase(it);
                }
            }
            FOR(i,1,na) {
                __typeof(s.begin()) it = s.lower_bound(a[i]);
                if (it == s.end()) {
                    can = false;
                    break;
                }
                else {
                    res += *it - a[i];
                    s.erase(it);
                }
            }
            while (!s.empty()) {
                res += *s.begin();
                s.erase(s.begin());
            }
            if (can) {
                best = max(best, res);
            }
        }

        // Only kill xa of them
        sort(a+1, a+na+1);
        sort(x+1, x+n+1);
        FOR(xa,1,na) {
            int res = 0;
            bool can = true;

            FOR(i,1,xa) {
                int cura = a[i];
                int curx = x[n-xa+i];

                if (curx < cura) {
                    can = false;
                    break;
                }
                else res += curx - cura;
            }

            if (can) best = max(best, res);
        }

        cout << best << endl;
    }
    return 0;
}
