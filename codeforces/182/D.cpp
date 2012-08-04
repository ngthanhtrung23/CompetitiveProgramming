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
const int MN = 100111;

char a[MN], b[MN];
int la, lb;

bool check(int l) {
    int now = 0;
    REP(i,la) {
        if (a[i] != a[now]) return false;
        ++now; if (now == l) now = 0;
    }
    now = 0;
    REP(i,lb) {
        if (b[i] != a[now]) return false;
        ++now; if (now == l) now = 0;
    }
    return true;
}

int main() {
    while (gets(a)) {
        gets(b);
        la = strlen(a);
        lb = strlen(b);
        int res = 0;
        FOR(i,1,la)
        if (la % i == 0 && lb % i == 0)
            if (check(i)) {
                ++res;
            }
        printf("%d\n", res);
    }
    return 0;
}
