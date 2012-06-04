//#pragma comment(linker, "/STACK:66777216")
#include <iomanip>
#include <sstream>
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
#include <bitset>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
#define PR0(a,n) cout << #a << " = "; REP(i,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int h[5][5];

void inp() {
    FOR(i,1,4) {
        FOR(j,i+1,4) {
            cin >> h[i][j];
        }
    }
}

const int oo = 1000111000;
int x[10], now, a[10][10], b[10], save[10], best = 1000111000;
char s[5][400111];

char cur[5];

void pt(int col, char aa, char bb, char c, char d) {
    cur[1] = aa;
    cur[2] = bb;
    cur[3] = c;
    cur[4] = d;
    int row = 0;
    FOR(i,1,4) FOR(j,i+1,4) {
        ++row;
        if (cur[i] != cur[j]) a[row][col] = 1;
        else a[row][col] = 0;
        b[row] = h[i][j];
    }
}

bool check() {
    pt(1, 'a', 'a', 'a', 'b');
    pt(2, 'a', 'a', 'b', 'a');
    pt(3, 'a', 'a', 'b', 'b');
    pt(4, 'a', 'b', 'a', 'a');
    pt(5, 'a', 'b', 'a', 'b');
    pt(6, 'a', 'b', 'b', 'a');
    pt(7, 'a', 'b', 'b', 'b');
    
    bool hasSolution = false;
        
    FOR(col,1,7) {
        if (!a[col][col]) {
            int save = 0;
            FOR(i,col+1,7) if (a[i][col]) {
                save = i;
                break;
            }
            
            FOR(j,1,7) swap(a[col][j], a[save][j]);
            swap(b[col], b[save]);
        }
        
        FOR(i,col+1,7) if (a[i][col]) {
            int p1 = a[i][col], p2 = a[col][col];
            FOR(j,1,7) a[i][j] = a[i][j] * p2 - a[col][j] * p1;
            b[i] = b[i] * p2 - b[col] * p1;
        }
    }
    
    FOR(t,0,400000) {
        x[7] = t;
        bool ok = true;
        FORD(i,6,1) {
            int t = b[i];
            FOR(j,i+1,7) t -= a[i][j] * x[j];
            if (!a[i][i]) {
                ok = false;
                break;
            }
            if (t % a[i][i]) {
                ok = false;
                break;
            }
            x[i] = t / a[i][i];
            if (x[i] < 0 || x[i] > 400000) {
                ok = false;
                break;
            }
        }
        if (ok) {
            int sum = 0;
            FOR(i,1,7) sum += x[i];
            if (sum <= 400000) {
                if (sum < best) {
                    best = sum;
                    FOR(i,1,7) save[i] = x[i];
                }
                hasSolution = true;
            }
        }
    }
    FOR(i,1,7) x[i] = save[i];
    return hasSolution;
}

void add(int k, char a, char b, char c, char d) {
    FOR(x,1,k) {
        ++now;
        s[1][now] = a;
        s[2][now] = b;
        s[3][now] = c;
        s[4][now] = d;
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    inp();
    if (!check()) {
        puts("-1");
        return 0;
    }
    now = 0;
    add(x[1], 'a', 'a', 'a', 'b');
    add(x[2], 'a', 'a', 'b', 'a');
    add(x[3], 'a', 'a', 'b', 'b');
    add(x[4], 'a', 'b', 'a', 'a');
    add(x[5], 'a', 'b', 'a', 'b');
    add(x[6], 'a', 'b', 'b', 'a');
    add(x[7], 'a', 'b', 'b', 'b');
    
    cout << best << endl;
    FOR(i,1,4) {
        FOR(x,1,best) putchar(s[i][x]);
        puts("");
    }
    return 0;
}
