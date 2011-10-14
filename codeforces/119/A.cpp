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

int gcd(int a, int b) {
    if (!a) return b;
    if (!b) return a;
    return gcd(b, a%b);
}

int main() {
//    freopen("A.in", "r", stdin);
//    freopen("A.out", "w", stdout);
    int a, b, n;
    cin >> a >> b >> n;
    int turn = 0;
    while (true) {
        int g;
        if (!turn) g = gcd(a, n);
        else g = gcd(b, n);
        n -= g;
        if (!n) break;
        turn = 1 - turn;
    }
    printf("%d", turn);
    return 0;
}
