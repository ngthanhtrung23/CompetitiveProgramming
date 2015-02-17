#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
//#include <conio.h>
using namespace std;
#define FOR(i, a, b) for(int i=a; i<=b; i++)
#define DOW(i, a, b) for(int i=a; i>=b; i--)
#define FOREACH(it, c) for(typeof(c.begin()) it=c.begin(); it!=c.end(); it++)
#define RESET(c, val) memset(c, val, sizeof(c))

int n, le;
string s;
char fir, las;
int f[300][300];

int main() {
    //freopen("test.inp", "r", stdin);
    //freopen(".out", "w", stdout);
    scanf("%d\n", &n);
    int res=0;
    for(char c1='a'; c1<='z'; c1++) for(char c2='a'; c2<='z'; c2++) f[c1][c2]=-1000000000;
    FOR(i, 1, n) {
        getline(cin, s); le=s.length();
        fir=s[0]; las=s[le-1];
        for(char c='a'; c<='z'; c++) 
            if (f[c][fir]>=0) f[c][las]=max(f[c][las], f[c][fir]+le);
        f[fir][las]=max(f[fir][las], le);
    }
    for(char c='a'; c<='z'; c++) res=max(res, f[c][c]);
    cout << res;
    //getch();
    return 0;
}