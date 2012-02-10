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

char a[100111], b[1011];
int next[1011], prev[1011], match[2][100111], m, n;

void init() {
    next[0] = -1; int j = -1;
    FOR(i,1,n-1) {
        while (j >= 0 && b[i] != b[j+1]) j = next[j];
        if (b[i] == b[j+1]) j++;
        next[i] = j;
    }
    prev[n-1] = n; j = n;
    FORD(i,n-2,0) {
        while (j < n && b[i] != b[j-1]) j = prev[j];
        if (b[i] == b[j-1]) j--;
        prev[i] = j;
    }
    
//    REP(i,n) cout << next[i] << ' '; puts("");
//    REP(i,n) cout << prev[i] << ' '; puts("");
}

void kmp() {
    int j = -1;
    FOR(i,0,m-1) {
        while (j >= 0 && a[i] != b[j+1]) j = next[j];
        if (a[i] == b[j+1]) j++;
        match[0][i] = j;
        if (j == n-1) j = next[j];
    }
    j = n;
    FORD(i,m-1,0) {
        while (j < n && a[i] != b[j-1]) j = prev[j];
        if (a[i] == b[j-1]) j--;
        match[1][i] = j;
        if (j == 0) j = prev[j];
    }
    
//    REP(i,m) cout << match[0][i] << ' '; puts("");
//    REP(i,m) cout << match[1][i] << ' '; puts("");
}

int check() {
    n = strlen(b), m = strlen(a);
    init();
    kmp();
    FOR(i,1,m-1) match[0][i] = max(match[0][i-1], match[0][i]);
    FORD(i,m-2,0) match[1][i] = min(match[1][i+1], match[1][i]);
    
    FOR(i,0,m-2) if (match[0][i]+1 >= match[1][i+1]) return 1;
    return 0;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    gets(a);
    int q; scanf("%d\n", &q);
    int res = 0;
    while (q--) {
        gets(b);
        if (strlen(b) == 1) continue;
        res += check();
    }
    cout << res;
    return 0;
}
