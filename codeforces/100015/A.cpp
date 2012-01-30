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
#include <sstream>

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

ll p3[30];

char xoay(int x, int c) {
    if (x == 0) return c;
    if (x == 2) return xoay(1, xoay(1, c));
    if (c == 'R') return 'P';
    else if (c == 'P') return 'S';
    else return 'R';
}

char get(long long n, int k) {
    if (n == 0) return 'R';
    if (n == 1) return 'P';
    if (n == 2) return 'S';
    
    int x = n / p3[k];
    char c = get(n%p3[k], k-1);
    return xoay(x, c);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    long long n;
    p3[0] = 1; FOR(i,1,26) p3[i] = p3[i-1] * 3LL;
    while (cin >> n && n) {
        printf("%c\n", xoay(1,get(n-1, 26)));
    }
    return 0;
}
