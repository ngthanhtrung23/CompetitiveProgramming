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

char s[100111];

bool form1() {
    int r, c;
    int l = strlen(s);
    REP(i,l) if (s[i] == 'R') r = i; else if (s[i] == 'C') c = i;
    
    if (r != 0) return false;
    if (c == r + 1) return false;
    FOR(i,r+1,c-1) if (s[i] < '0' || s[i] > '9') return false;
    FOR(i,c+1,l-1) if (s[i] < '0' || s[i] > '9') return false;
    return true;
}

void convert1(int b) {
    if (b <= 0) return ;
    if (b <= 26) printf("%c", b - 1 + 'A');
    else {
        int last = b % 26; if (!last) last = 26;
        convert1((b-1) / 26);
        printf("%c", last - 1 + 'A');
    }
}

void solve1() {
    int a, b;
    sscanf(s, "R%dC%d", &a, &b);
    convert1(b); printf("%d\n", a);
}

int convert2(int l, int r) {
    int cur = 1, res = 0;
    FORD(i,r,l) {
        res += (s[i] - 'A' + 1) * cur;
        cur *= 26;
    }
    return res;
}

void solve2() {
    int first;
    int l = strlen(s);
    REP(i,l) if (s[i] >= '0' && s[i] <= '9') {
        first = i;
        break;
    }
    
    int x = convert2(0,first-1);
    putchar('R');
    FOR(i,first,l-1) {
        printf("%c", s[i]);
    }
    putchar('C');
    printf("%d\n", x);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int ntest; scanf("%d\n", &ntest);
    while (ntest--) {
        gets(s);
        if (form1()) solve1();
        else solve2();
    }
    return 0;
}
