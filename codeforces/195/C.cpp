#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <complex>

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(i,a) for(int i = 0; i < a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(x,n) cout << #x << " = "; FOR(__,1,n) cout << x[__] << ' '; puts("");
#define PR0(x,n) cout << #x << " = "; REP(__,n) cout << x[__] << ' '; puts("");
using namespace std;

struct Statement {
    string type;
    string arg1, arg2;
} a[100111];

int n, match[100111], st[100111];
char c[1000111];

int main() {
    while (scanf("%d\n", &n) == 1) {
        FOR(i,1,n) {
            gets(c);
            bool conv = false;
            REP(x,strlen(c)) {
                if (c[x] == ' ' && conv) c[x] = '_';
                if (c[x] == '"') conv = !conv;
            }
            REP(x,strlen(c))
                if (c[x] == '(' || c[x] == ')' || c[x] == '"' || c[x] == ',') c[x] = ' ';
            istringstream sin(c);
            sin >> a[i].type;
            if (a[i].type == "throw") sin >> a[i].arg1;
            else {
                if (a[i].type == "catch") sin >> a[i].arg1 >> a[i].arg2;
                REP(x,a[i].arg2.length())
                if (a[i].arg2[x] == '_') a[i].arg2[x] = ' ';
            }
        }
        int top = 0;
        FOR(i,1,n) {
            if (a[i].type == "try") {
                st[++top] = i;
            }
            else if (a[i].type == "catch") {
                match[i] = st[top];
                match[st[top]] = i;
                --top;
            }
        }

        int u = 0;
        bool ok = false;
        FOR(i,1,n) if (a[i].type == "throw") u = i;

        FORD(i,u-1,1)
        if (a[i].type == "try" && match[i] > u && a[match[i]].arg1 == a[u].arg1) {
            puts(a[match[i]].arg2.c_str());
            ok = true;
            break;
        }
        if (!ok) puts("Unhandled Exception");
    }
    return 0;
}
