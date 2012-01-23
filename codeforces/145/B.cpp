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
#include <sstream>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

int INP,AM;
#define BUFSIZE (1<<10)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (feof(stdin)) memset(BUF,0,sizeof BUF); else fread(BUF,1,BUFSIZE,stdin); \
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

const double PI = acos(-1.0);

bool can(int start, int n4, int n7, int n47, int n74) {
    if (start == 7) return can(4, n7, n4, n74, n47);
    if (abs(n47 - n74) > 1) return false;
    if (n4 <= 0) return false;
    if (n7 < 0) return false;
    if (n47 < 0) return false;
    if (n74 < 0) return false;
    
    if (n4 && n7 && !n47 && !n74) return false;
    
    if (n47 == n74) {
        return n4 >= n47+1 && n7 >= n47;
    }
    else if (n47 > n74) {
        return n4 >= n47 && n7 >= n47;
    }
    else return false;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n4, n7, n47, n74;
    while (cin >> n4 >> n7 >> n47 >> n74) {
        int must = 0, last = 0;
        if (!can(4,n4,n7,n47,n74) && !can(7,n4,n7,n47,n74)) {
            puts("-1");
            continue;
        } 
        while (n4 || n7) {
            int cur;
            if (must) {
                cur = must;
            }
            else if (can(4,n4,n7,n47,n74)) cur = 4;
            else if (can(7,n4,n7,n47,n74)) cur = 7;
            else {
                cout << "-1";
                break;
            }
            printf("%d", cur);

            if (cur == 4) {
                n4--;
                if (can(4, n4, n7, n47, n74)) {
                    must = 4;
                }
                else {
                    must = 7;
                    n47--;
                }
            }
            else {
                n7--;
                if (can(4, n4, n7, n47, n74-1)) {
                    must = 4;
                    n74--;
                }
                else {
                    must = 7;
                }
            }

            last = cur;
        }
        puts("");
    }
    return 0;
}
