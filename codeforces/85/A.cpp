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

char a[10][111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n; cin >> n;
    if (n == 1) {
        puts("a"); puts("a"); puts("b"); puts("b");
        return 0;
    }
    else if (n == 2) {
        puts("aa");
        puts("bb");
        puts("cc");
        puts("dd");
        return 0;
    }
    else if (n % 2 == 1) {
        a[1][1] = a[2][1] = 'a';
        a[3][n] = a[4][n] = 'a';
        int now = 1;
        for(int j = 2; j <= n; j += 2) {
            if (now) a[1][j] = a[1][j+1] = 'b'; else a[1][j] = a[1][j+1] = 'x';
            if (now) a[2][j] = a[2][j+1] = 'c'; else a[2][j] = a[2][j+1] = 'y';
            
            if (now) a[3][j-1] = a[3][j] = 'd'; else a[3][j-1] = a[3][j] = 'z';
            if (now) a[4][j-1] = a[4][j] = 'e'; else a[4][j-1] = a[4][j] = 't';
            now = 1-now;
        }
        
        FOR(i,1,4) {
            FOR(j,1,n) cout << a[i][j];
            puts("");
        }
    }
    else {
        a[2][1] = a[3][1] = a[2][n] = a[3][n] = 'u';
        
        int now = 1;
        for(int j = 2; j <= n; j += 2) {
            if (now) a[1][j-1] = a[1][j] = 'a'; else a[1][j-1] = a[1][j] = 'x';
            
            if (j + 1 <= n) {
                if (now) a[2][j] = a[2][j+1] = 'b'; else a[2][j] = a[2][j+1] = 'y';
                
                if (now) a[3][j] = a[3][j+1] = 'c'; else a[3][j] = a[3][j+1] = 'z';
            }
            if (now) a[4][j-1] = a[4][j] = 'd'; else a[4][j-1] = a[4][j] = 't';
            
            now = 1 - now;
        }
        
        FOR(i,1,4) {
            FOR(j,1,n) cout << a[i][j];
            puts("");
        }
    }
    return 0;
}
