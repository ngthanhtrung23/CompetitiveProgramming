#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <fstream>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i >= _b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)
#define PB push_back
#define MP make_pair
#define F first
#define S second
using namespace std;

char a[11][11];

bool ok() {
    REP(i,3) REP(j,3) {
        if (a[i][j] == a[i][j+1]
                && a[i][j] == a[i+1][j]
                && a[i][j] == a[i+1][j+1]) {
            return true;
        }
    }
    return false;
}

bool check() {
    if (ok()) return true;
    REP(i,4) REP(j,4) {
        if (a[i][j] == '.') a[i][j] = '#';
        else a[i][j] = '.';

        if (ok()) {
            return true;
        }

        if (a[i][j] == '.') a[i][j] = '#';
        else a[i][j] = '.';
    }
    return false;
}

int main() {
    while (gets(a[0])) {
        FOR(i,1,3) gets(a[i]);

        if (check()) puts("YES");
        else puts("NO");
    }
    return 0;
}
