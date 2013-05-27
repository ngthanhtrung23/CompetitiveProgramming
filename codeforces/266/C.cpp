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
const int MN = 1011;

int cntRow[MN], cntCol[MN];
int n;
pair<int,int> a[MN];

vector< pair<int, pair<int,int> > > res;

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n-1) scanf("%d%d", &a[i].first, &a[i].second);
        res.clear();

        FORD(turn,n,2) {
            memset(cntRow, 0, sizeof cntRow);
            memset(cntCol, 0, sizeof cntCol);

            FOR(i,1,n-1)
            if (a[i].first <= turn && a[i].second <= turn) {
                ++cntRow[a[i].first];
                ++cntCol[a[i].second];
            }

            if (cntCol[turn] == 0) {
            }
            else {
                FOR(j,1,turn-1) if (cntCol[j] == 0) {
                    res.push_back(make_pair(2, make_pair(j, turn)));

                    FOR(t,1,n-1)
                    if (a[t].second == j) a[t].second = turn;
                    else if (a[t].second == turn) a[t].second = j;
                    break;
                }
            }

            if (cntRow[turn]) {
            }
            else {
                FOR(i,1,turn-1) if (cntRow[i]) {
                    res.push_back(make_pair(1, make_pair(i, turn)));

                    FOR(t,1,n-1)
                    if (a[t].first == i) a[t].first = turn;
                    else if (a[t].first == turn) a[t].first = i;
                }
            }
        }
        printf("%d\n", res.size());
        REP(i,res.size())
            printf("%d %d %d\n", res[i].first, res[i].second.first, res[i].second.second);
    }
    return 0;
}
