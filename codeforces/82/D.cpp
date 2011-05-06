#pragma comment(linker, "/STACK:16777216")
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
#include <sstream>
#include <iomanip>

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

int f[1011][1011], a[1011], n, tr[1011][1011], saven;

void u(int ii, int jj, int i, int j, int a, int b) {
    int now = f[i][j] + max(a, b);
    if (f[ii][jj] == -1 || f[ii][jj] > now) {
        f[ii][jj] = now;
        tr[ii][jj] = j;
    }
}

void trace(int N, int u) {
    if (N == 3) {
        if (u == 1) cout << "2 3\n";
        else if (u == 2) cout << "1 3\n";
        else if (u == 3) cout << "1 2\n";
        return ;
    }
    trace(N-2, tr[N][u]);
    if (u == tr[N][u]) cout << N-1 << ' ' << N << endl;
    else if (u == N-1) cout << tr[N][u] << ' ' << N << endl;
    else cout << tr[N][u] << ' ' << N-1 << endl;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d", &n); saven = n;
    FOR(i,1,n) scanf("%d", &a[i]);
    if (n == 1) {
        cout << a[1] << endl;
        cout << 1 << endl;
        return 0;
    }
    if (n == 2) {
        cout << max(a[1], a[2]) << endl;
        cout << "1 2\n";
        return 0;
    }
    
    if (n % 2 == 1) {
        n++;
        a[n] = 0;
    }
    
    memset(f, -1, sizeof f);
    f[3][3] = max(a[1], a[2]);
    f[3][2] = max(a[1], a[3]);
    f[3][1] = max(a[2], a[3]);
    
    for(int i = 3; i < n-1; i += 2)
    FOR(j,1,n)
    if (f[i][j] >= 0) {
        u(i+2,j, i, j, a[i+1], a[i+2]);
        u(i+2,i+1, i, j, a[j], a[i+2]);
        u(i+2,i+2, i, j, a[j], a[i+1]);
    }
    
    int res = 1000111000;
    FOR(i,1,n)
    if (f[n-1][i] >= 0) {
        res = min(res, f[n-1][i] + max(a[i], a[n]));
    }
    cout << res << endl;
    FOR(i,1,n)
        if (res == f[n-1][i] + max(a[i], a[n])) {
            trace(n-1, i);
            if (n == saven) cout << i << ' ' << n << endl;
            else cout << i << endl;
            return 0;
        }
    return 0;
}
