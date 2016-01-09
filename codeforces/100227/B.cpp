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

int x[55], gh[55];
map<int,int> cnt;

int main() {
    ios :: sync_with_stdio(false);
    int n, s;
    while (cin >> n && n) {
        FOR(i,1,n) cin >> x[i];
        cin >> s;

        cnt.clear();
        set<int> res;
        set<int> :: iterator it;

        FOR(k,1,100000) {
            FOR(i,1,n) {
                long long t = ((x[i]-2) * (long long) k * (k+1)) / 2 - (long long) k * (x[i]-3);
                if (res.size() >= 5) {
                    it = res.end(); --it;
                    if (t > *it) break;
                }

                gh[i] = k;
                if (t >= s && t <= 2147483647) {
                    cnt[t]++;
                    if (cnt[t] >= 2) {
                        res.insert(t);
                        if (res.size() > 5) {
                            it = res.end(); --it;
                            res.erase(it);
                        }
                    }
                }
            }
        }
        for(it = res.begin(); it != res.end(); ++it) {
            cout << *it << ':';
            FOR(i,1,n) {
                int l = 1, r = gh[i], res = 1;
                while (l <= r) {
                    int k = (l + r) >> 1;
                    long long t = ((x[i]-2) * (long long) k * (k+1)) / 2 - (long long) k * (x[i]-3);
                    if (t <= *it) {
                        res = k;
                        l = k + 1;
                    }
                    else r = k - 1;
                }
                int k = res;
                long long t = ((x[i]-2) * (long long) k * (k+1)) / 2 - (long long) k * (x[i]-3);
                if (t == *it) {
                    cout << x[i] << ' ';
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}