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

char a[100111];
int n;
int f[111][225][2][55];

char rev(char now) {
    if (now == 'T') return 'F';
    else return 'T';
}

void apply(int i, int dir, char now, int &i2, int &dir2) {
    if (now == 'F') {
        if (dir == 1) i2 = i + 1; else i2 = i - 1;
        dir2 = dir;
    }
    else {
        i2 = i;
        dir2 = 1 - dir;
    }
}

int ab(int x) {
    if (x < 0) return -x;
    else return x;
}

int main() {
    scanf("%s\n", &a[0]); scanf("%d", &n);
    int l = strlen(a);
    f[0][111][1][0] = 1;

    FOR(k,0,l-1) FOR(i,111-k,111+k) REP(dir,2) FOR(nchange,0,n)
    if (f[k][i][dir][nchange]) {
        int i2, dir2;
        char now = a[k];
        apply(i, dir, now, i2, dir2);
        f[k+1][i2][dir2][nchange] = 1;
//        cout << k << ' ' << i << ' ' << dir << ' ' << nchange << ' ' << i2 << ' ' << dir2 << endl;
        
        now = rev(now);
        apply(i, dir, now, i2, dir2);
        f[k+1][i2][dir2][nchange + 1] = 1;
    }
//    cout << f[1][112][1][0] << ' ' << f[2][113][1][0] << endl;
    int res = 0;
    FOR(i,0,222) REP(dir,2) FOR(nchange,0,n) if (nchange % 2 == n % 2 && f[l][i][dir][nchange]) {
        res = max(res, ab(i - 111));
    }
    cout << res << endl;
    return 0;
}
