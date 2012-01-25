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

set<string> S;

const int r[][6] = {
    {0,1,2,3,4,5},
    {0,2,3,4,1,5},
    {0,3,4,1,2,5},
    {0,4,1,2,3,5},
    {5,3,2,1,4,0},
    {5,2,1,4,3,0},
    {5,1,4,3,2,0},
    {5,4,3,2,1,0},
    
    {1,2,0,4,5,3},
    {1,0,4,5,2,3},
    {1,4,5,2,0,3},
    {1,5,2,0,4,3},
    {3,4,0,2,5,1},
    {3,0,2,5,4,1},
    {3,2,5,4,0,1},
    {3,5,4,0,2,1},
    
    {2,0,1,5,3,4},
    {2,1,5,3,0,4},
    {2,5,3,0,1,4},
    {2,3,0,1,5,4},
    {4,5,1,0,3,2},
    {4,1,0,3,5,2},
    {4,0,3,5,1,2},
    {4,3,5,1,0,2},
};

char s[10];
bool mark[10];

bool check(string s) {
    REP(rot,24) {
        string cur = "";
        REP(x,6) cur = cur + s[r[rot][x]];
        if (S.find(cur) != S.end()) return false;
    }
    return true;
}

void attempt(int i, string cur) {
    if (i == 6) {
        if (check(cur)) S.insert(cur);
        return ;
    }
    REP(x,6) if (!mark[x]) {
        mark[x] = true;
        attempt(i+1, cur + s[x]);
        mark[x] = false;
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    gets(s);
    attempt(0, "");
    cout << S.size() << endl;
    return 0;
}
