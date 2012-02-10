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
const int BASE = 1000000007;

char s[1011];

int f[777][777][3][3], st[1011], match[1011];

bool can(int a, int b) { // neighbour
    if (!a || !b) return true;
    if (a != b) return true;
    return false;
}

bool ok(int a, int b) { // match
    if (a && b) return false;
    if (!a && !b) return false;
    return true;
}

int get(int l, int r, int x, int y) {
    if (f[l][r][x][y] >= 0) return f[l][r][x][y];
    if (l+1 == r) {
        if (ok(x, y)) return 1;
        else return 0;
    }
    
    int res = 0;
    if (match[l] == r) {
        if (x && y) return 0;
        if (!x && !y) return 0;
        
        REP(u,3) REP(v,3) if (can(x, u) && can(v, y)) {
            res = (res + get(l+1, r-1, u, v)) % BASE;
        }
    }
    else {
        int i, j = match[r]; i = j - 1;
//        cout << i << ' ' << j << endl;
        REP(u,3) REP(v,3) if (can(u, v)) {
            res = (res + get(l,i,x,u) * (long long) get(j,r,v,y)) % BASE;
        }
    }
    return f[l][r][x][y] = res;
}

int sum = 0, color[1011];

void attempt(int i) {
    if (i == strlen(s)) {
        if (i == 3) {
            FOR(x,0,strlen(s) - 1) cout << color[x] << ' '; puts("");
        }
        sum++;
        return ;
    }
    REP(x,3) {
        color[i] = x;
        if (i && !can(color[i-1], color[i])) continue;
        if (s[i] == ')' && !ok(color[i], color[match[i]])) continue;
        
        attempt(i+1);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (gets(s)) {
        int top = 0;
        REP(i,strlen(s)) {
            if (s[i] == '(') {
                top++;
                st[top] = i;
            }
            else {
                int j = st[top]; top--;
                match[i] = j;
                match[j] = i;
            }
        }
        
    //    REP(i,strlen(s)) cout << match[i] << ' '; puts("");
        
        memset(f, -1, sizeof f);
        int res = 0;
        REP(x,3) REP(y,3) {
            res = (res + get(0,strlen(s) - 1, x, y)) % BASE;
        }
        cout << res << endl;
    }
    return 0;
}
