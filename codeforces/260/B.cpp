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

int nDate[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
char s[100111];

bool digit(char c) {
    return (c >= '0' && c <= '9');
}
bool dash(char c) {
    return c == '-';
}

bool check(int i) {
    return digit(s[i]) && digit(s[i+1]) && dash(s[i+2])
            && digit(s[i+3]) && digit(s[i+4]) && dash(s[i+5])
            && digit(s[i+6]) && digit(s[i+7]) && digit(s[i+8]) && digit(s[i+9]);
}

int value(int i) {
    return (s[i] - '0') * 10 + (s[i+1] - '0');
}

int cnt[2020][20][33];

int main() {
    while (gets(s)) {
        memset(cnt, 0, sizeof cnt);
        int l = strlen(s);
        REP(i,l-9) if (check(i)) {
            int date = value(i);
            int month = value(i+3);
            int year = value(i+6) * 100 + value(i+8);

            if (2013 <= year && year <= 2015 && month > 0 && month <= 12 && date > 0 && date <= nDate[month]) {
                ++cnt[year][month][date];
            }
        }

        int ry = 2013, rm = 1, rd = 1;

        FOR(year,2013,2015)
        FOR(month,1,12)
        FOR(date,1,nDate[month])
            if (cnt[year][month][date] > cnt[ry][rm][rd]) {
                ry = year;
                rm = month;
                rd = date;
            }
        if (rd < 10) putchar('0');
        cout << rd << '-';
        if (rm < 10) putchar('0');
        cout << rm << '-' << ry << endl;
    }
    return 0;
}
