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

char s[1011];

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool checkRC() {
    if (strchr(s, 'R') == NULL || strchr(s, 'C') == NULL) return false;
    int r = strchr(s, 'R') - s;
    int c = strchr(s, 'C') - s;

    if (r != 0) return false;
    if (c == strlen(s) - 1) return false;
    if (r == c-1) return false;

    FOR(i,r+1,c-1) if (!isDigit(s[i])) return false;
    FOR(i,c+1,strlen(s)-1) if (!isDigit(s[i])) return false;
    return true;
}

void conv1() {
    stringstream ss;
    int r = strchr(s, 'R') - s;
    int c = strchr(s, 'C') - s;
    FOR(i,c+1,strlen(s)-1) ss << s[i];
    int x; ss >> x;

    int len = 0, now = 1, u = x;
    while (u > 0) {
        now *= 26;
        u -= now;
        ++len;
    }
    u += now - 1;

    FOR(i,1,len) {
        now /= 26;
        putchar(u / now + 'A');
        u %= now;
    }

    FOR(i,r+1,c-1) putchar(s[i]);
    puts("");
}

void conv2() {
    int l = 1;
    while (!isDigit(s[l-1])) ++l;
    --l;
    putchar('R');
    FOR(i,l,strlen(s)-1) putchar(s[i]);
    putchar('C');

    int res = 1, now = 1;
    FOR(i,1,l-1) now *= 26, res += now;
    REP(i,l) {
        res += (s[i] - 'A') * now;
        now /= 26;
    }
    printf("%d\n", res);
}

int main() {
    int ntest; scanf("%d\n", &ntest);
    while (ntest--) {
        memset(s, 0, sizeof s);
        gets(s);
        if (checkRC()) conv1();
        else conv2();
    }
    return 0;
}