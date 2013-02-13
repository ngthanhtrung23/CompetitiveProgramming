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
const int MN = 200111;

long long MOD;
int n, a[MN], b[MN];
pair<ll,ll> gt[MN];
ll p2[MN];
map<int,int> cnt, diff;
set< pair<int,int> > exists;

void insert(int x, int y) {
    cnt[x]++;
    if (exists.find(MP(x,y)) == exists.end()) {
        diff[x]++;
        exists.insert(MP(x, y));
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,1,n) scanf("%d", &b[i]);
        cin >> MOD;

        p2[0] = 1;
        FOR(i,1,200000) p2[i] = (p2[i-1] * 2) % MOD;
        gt[0] = MP(1, 0);
        FOR(i,1,200000) {
            ll now = i;
            int p = 0;
            while (now % 2 == 0) {
                now /= 2;
                ++p;
            }

            gt[i] = MP(gt[i-1].F * now % MOD, gt[i-1].S + p);
        }

        cnt.clear(); diff.clear(); exists.clear();

        FOR(i,1,n) insert(a[i], i);
        FOR(i,1,n) insert(b[i], i);

        ll res = 1;
        for(map<int,int> :: iterator it = cnt.begin(); it != cnt.end(); ++it) {
            // cout << it->F << ' ' << cnt[it->F] << ' ' << diff[it->F] << endl;

            res = res * gt[it->S].F % MOD;
            int repeat = it->S - diff[it->F];
            res = (res * p2[gt[it->S].S - repeat]) % MOD;
        }
        cout << res % MOD << endl;
    }
    return 0;
}
