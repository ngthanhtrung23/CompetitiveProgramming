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

char s[1000111];
string a, b;

int value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10;
}

int get(int base, string s) {
    int res = 0;
    REP(i,s.length()) {
        res = (res * base) + value(s[i]);
        if (res > 59) return res;
    }
    return res;
}

bool check(int base) {
    if (get(base, a) <= 23 && get(base, b) <= 59) return true;
    else return false;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    gets(s);
    REP(i,strlen(s)) if (s[i] == ':') s[i] = ' ';
    int nn = 0;
    REP(i,strlen(s)) {
        nn = max(nn, value(s[i]) + 1);
    }
    istringstream sin(s);
    sin >> a >> b;
    if (check(66)) puts("-1");
    else {
        int cnt = 0;
        FOR(base,nn,66) if (check(base)) {
            printf("%d ", base);
            cnt++;
        }
        if (!cnt) puts("0");
    }
    return 0;
}
