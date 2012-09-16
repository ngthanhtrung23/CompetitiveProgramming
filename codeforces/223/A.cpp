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
int INP,AM;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (feof(stdin)) memset(BUF, 0, sizeof BUF); else fread(BUF,1,BUFSIZE,stdin); \
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

char tmp[100111];
string s;
int st[100111], top, cnt[100111], match[100111];

int main() {
    while (gets(tmp)) {
        int l = strlen(tmp);
        s = ' ' + string(tmp);
        top = 0; st[top] = 0;

        cnt[0] = 0;
        FOR(i,1,l) {
            cnt[i] = cnt[i-1];
            if (s[i] == '[') ++cnt[i];
        }

        int res = -1, save1, save2;
        memset(match, -1, sizeof match);
        FOR(i,1,l) {
            if (s[i] == '(') {
                st[++top] = i;
            }
            else if (s[i] == '[') {
                st[++top] = i;
            }
            else if (s[i] == ']') {
                if (s[st[top]] == '[') {
                    if (match[st[top]-1] >= 0) st[top] = match[st[top]-1];
                    match[i] = st[top];

                    int now = cnt[i] - cnt[st[top] - 1];
                    if (now >= res) {
                        res = now;
                        save1 = st[top];
                        save2 = i;
                    }
                    --top;
                }
                else top = 0;
            }
            else if (s[i] == ')') {
                if (s[st[top]] == '(') {
                    if (match[st[top]-1] >= 0) st[top] = match[st[top]-1];
                    match[i] = st[top];

                    int now = cnt[i] - cnt[st[top] - 1];
                    if (now >= res) {
                        res = now;
                        save1 = st[top];
                        save2 = i;
                    }
                    --top;
                }
                else top = 0;
            }
        }
        if (res < 0) {
            puts("0");
            continue;
        }
        printf("%d\n", res);
        FOR(i,save1,save2) putchar(s[i]);
        puts("");
    }
    return 0;
}
