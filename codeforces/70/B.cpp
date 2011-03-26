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
using namespace std;

const double PI = acos(-1.0);
int len, a[10111], n, maxLen, f[10111];
const char imp[] = "Impossible";
char s[10111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    len = 0; n = 0;
    char c;
    scanf("%d\n", &maxLen);
    gets(s);
    REP(x,strlen(s)) {
        c = s[x];
        if (c == '.' || c == '?' || c == '!') {
            len++;
            a[n++] = len;
            len = 0;
        }
        else if (c == ' ') {
            if (len) len++;
        }
        else len++;
    }
    if (len) {
        puts(imp);
        return 0;
    }
    REP(i,n) if (a[i] > maxLen) {
        puts(imp);
        return 0;
    }
    REP(i,n) {
        if (!i) f[i] = 1;
        else f[i] = f[i-1] + 1;
        
        if (i) {
            int j = i - 1, now = a[i-1] + 1 + a[i];
            while (j > 0 && now <= maxLen) {
                j--;
                f[i] = min(f[i], f[j] + 1);
                now += a[j] + 1;
            }
            if (now <= maxLen) f[i] = min(f[i], 1);
        }
    }
    printf("%d\n", f[n-1]);
    return 0;
}
