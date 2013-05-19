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

int a[111], cnt[111];

int main() {
    int n;
    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) {
            cin >> a[i];
            cnt[a[i]]++;
        }
        vector<int> res; res.clear();

        while (cnt[0]--) res.push_back(0);

        if (cnt[100]) res.push_back(100);
        bool ok = false;
        FOR(i,1,9) if (cnt[i]) {
            ok = true;
            res.push_back(i);
            break;
        }

        for(int i = 10; i <= 90; i += 10) if (cnt[i]) {
            ok = true;
            res.push_back(i);
            break;
        }

        if (!ok) {
            FOR(i,11,99) if (i % 10 && cnt[i]) {
                res.push_back(i);
                break;
            }
        }

        printf("%d\n", res.size());
        REP(i,res.size()) printf("%d ", res[i]); puts("");
    }
    return 0;
}
