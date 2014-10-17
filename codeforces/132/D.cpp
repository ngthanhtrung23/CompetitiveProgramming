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
using namespace std;

const double PI = acos(-1.0);

char s[2][1000111];
int f[2][1000111], n, tr[2][1000111];

char rev(char c) {
    if (c == '1') return '0';
    else return '1';
}

set< pair<int, pair<int,int> > > S;

void add(int t, int i) {
    S.insert(MP(f[t][i], MP(t,i)));
}

void trace(int t, int i, int sign) {
//    cout << t << ' ' << i << ' ' << sign << endl;
    if (i == n) return ;
    if (tr[t][i] == 0) {
        if (s[t][i] == '1') {
            if (sign < 0) printf("-"); else printf("+");
            printf("2^%d\n", n-i-1);
            trace(t, i+1, sign);
        }
        else {
            trace(t, i+1, sign);
        }
    } else {
        if (sign < 0) printf("-"); else printf("+");
        printf("2^%d\n", n-i);
        trace(1-t, i, -sign);
    }
}

void solve() {
    REP(t,2) FOR(i,0,n) f[t][i] = 1000111000;

    f[0][n] = f[1][n] = 0;

    add(0, n); add(1, n);
    while (!S.empty()) {
        pair<int, pair<int,int> > cur = *S.begin();
        S.erase(S.begin());
        int t = cur.S.F, i = cur.S.S, l = cur.F;
        if (f[t][i] != l) continue;

//        cout << t << ' ' << i << ' ' << f[t][i] << endl;

        if (t == 0 && i == 0) {
            printf("%d\n", l);
            trace(0, 0, 1);
            return ;
        }
        if (i == 0) continue;

        int cost = f[t][i] + s[t][i-1] - '0';
        if (cost < f[t][i-1]) {
            f[t][i-1] = cost;
            tr[t][i-1] = 0;
            add(t, i-1);
        }
        cost = 1 + f[t][i];
        if (cost < f[1-t][i]) {
            f[1-t][i] = cost;
            tr[1-t][i] = 1;
            add(1-t, i);
        }
    }
}

int main() {
    scanf("%s", &s[0][1]);
    s[0][0] = '0';
    n = strlen(s[0]);
    bool need = false;
    FORD(i,n,0) {
        if (need) s[1][i] = rev(s[0][i]);
        else {
            s[1][i] = s[0][i];
            if (s[0][i] == '1') need = true;
        }
    }
//    cout << s[0] << ' ' << s[1] << ' ' << n << endl;

    solve();
    return 0;
}