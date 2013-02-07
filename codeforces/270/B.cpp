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

int a[100111];

int main() {
    #ifdef DEBUG_MODE
        freopen("input.txt", "r", stdin);
    #endif // DEBUG_MODE
    int n;
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        int nn = n + 1;
        int res = 0, now = 1;
        FORD(i,n,1) {
            if (a[i] > nn) {
                ++res;
                a[i] = --now;
            }
            nn = min(nn, a[i]);
        }
        printf("%d\n", res);
    }
    return 0;
}
