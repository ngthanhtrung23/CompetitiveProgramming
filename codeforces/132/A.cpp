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

char s[100111];
int last = 0;

void print(int c) {
    int res = 0;
    FOR(i,1,8) {
        res = res * 2 + c % 2;
        c /= 2;
    }
    printf("%d\n", (last - res + 256) % 256);
    last = res;
}

int main() {
    gets(s);
    REP(i,strlen(s)) {
        print(s[i]);
    }
    return 0;
}
