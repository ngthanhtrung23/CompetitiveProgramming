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

int n, m;

int get(int i, int s) {
    if (i == 1) return s - 1;
    else return (2*m - 1 - s) % (2*m-2);
}

int dist(int i, int j) {
    int res = j - i;
    if (res < 0) res += 2*m-2;
    return res;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d %d", &n, &m);
    while (n--) {
        int t, s, f;
        scanf("%d %d %d", &s, &f, &t);
        if (s == f) {
            printf("%d\n", t);
            continue;
        }
        int res = 1000111000;
        FOR(i,1,2) FOR(j,1,2) {
            res = min(res, dist(t % (2*m-2), get(i,s)) + dist(get(i,s), get(j, f)));
        }
        
        printf("%d\n", res + t);
    }
    return 0;
}
