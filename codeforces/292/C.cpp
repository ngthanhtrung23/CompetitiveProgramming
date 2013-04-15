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

int n, a[111], x[111], mark[111];

string add(string a, int u) {
    string res = a;
    if (res != "") res += '.';
    if (u >= 100) {
        res += (char) (u/100 + '0'); u %= 100;
        res += (char) (u/10 + '0'); u %= 10;
        res += (char) (u + '0');
    }
    else if (u >= 10) {
        res += (char) (u/10 + '0'); u %= 10;
        res += (char) (u + '0');
    }
    else {
        res += (char) (u + '0');
    }
    return res;
}

vector<string> all;

void solve(int i, int len, int seg, string cur) {
    if (i > len) {
        if (seg == 5) {
            all.push_back(cur);
            // cout << cur << endl;
        }
        return ;
    }
    if (seg > 4) return ;

    solve(i+1, len, seg+1, add(cur, x[i]));
    if (x[i] == 0) return ;
    if (i+1 <= len) solve(i+2, len, seg+1, add(cur, x[i] * 10 + x[i+1]));
    if (i+2 <= len && x[i] * 100 + x[i+1] * 10 + x[i+2] <= 255)
        solve(i+3, len, seg+1, add(cur, x[i] * 100 + x[i+1] * 10 + x[i+2]));
}

void attempt(int i, int len) {
    if (i > len) {
        bool ok = true;
        FOR(i,1,n) if (!mark[a[i]]) ok = false;

        if (ok) {
            // PR(x, len);
            solve(1, len, 1, "");
        }
        return ;
    }
    int j = len - i + 1;
    if (j < i) {
        x[i] = x[j];
        attempt(i+1, len);
    }
    else {
        FOR(t,1,n) {
            x[i] = a[t];
            mark[a[t]]++;
            attempt(i+1, len);
            mark[a[t]]--;
        }
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);

        all.clear();
        FOR(len,4,12) {
            attempt(1, len);
        }
        printf("%d\n", all.size());
        sort(all.begin(), all.end());
        all.resize(unique(all.begin(), all.end()) - all.begin());
        REP(i,all.size())
            puts(all[i].c_str());
    }
    return 0;
}
