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

char inp[500111];
char a[500111];
int m, n;

int encode(int i, int j) {
    return i*n + j;
}

const int BASE = 1000003;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int now = 0;
    scanf("%d %d\n", &m, &n);
    REP(i,m) {
        gets(inp);
        REP(j,n) a[now++] = inp[j];
    }
    
    int res = 1;
    REP(i,m) {
        int start[2];
        start[0] = start[1] = 0;
        REP(j,n) {
            if (j % 2 == 0) {
                if (a[encode(i,j)] == '1' || a[encode(i,j)] == '2') start[0] = 1;
                else if (a[encode(i,j)] == '3' || a[encode(i,j)] == '4') start[1] = 1;
            } else {
                if (a[encode(i,j)] == '1' || a[encode(i,j)] == '2') start[1] = 1;
                else if (a[encode(i,j)] == '3' || a[encode(i,j)] == '4') start[0] = 1;
            }
        }
        if (start[0] * start[1]) {
            puts("0");
            return 0;
        }
        if (start[0] + start[1]) {
        }
        else res = (res + res) % BASE;
    }
    
    
    REP(j,n) {
        int start[2];
        start[0] = start[1] = 0;
        REP(i,m) {
            if (i % 2 == 0) {
                if (a[encode(i,j)] == '1' || a[encode(i,j)] == '4') start[0] = 1;
                else if (a[encode(i,j)] == '3' || a[encode(i,j)] == '2') start[1] = 1;
            } else {
                if (a[encode(i,j)] == '1' || a[encode(i,j)] == '4') start[1] = 1;
                else if (a[encode(i,j)] == '3' || a[encode(i,j)] == '2') start[0] = 1;
            }
        }
        if (start[0] * start[1]) {
            puts("0");
            return 0;
        }
        if (start[0] + start[1]) {
        }
        else res = (res + res) % BASE;
    }
    
    cout << res;
    return 0;
}
