#include <iomanip>
#include <sstream>
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

int main() {
    freopen("continued.in", "r", stdin);
    freopen("continued.out", "w", stdout);
    int n, m;
    while (cin >> n >> m) {
        if (n == m) {
            puts("1");
            printf("1 ");
            FOR(i,1,m) putchar('9');
            puts("");
        }
        else if (n % m == 0) {
            puts("1");
            putchar('1');
            FOR(i,1,n-m) if (i % m == 0) putchar('1'); else putchar('0');
            putchar(' ');
            FOR(i,1,m) putchar('9');
            puts("");
        }
        else {
            if (n > m) {
                puts("3");
                putchar('1');
                FOR(i,1,n-m) if (i % m == 0) putchar('1'); else putchar('0');
                n %= m;
                putchar(' ');
            }
            else {
                puts("3");
                printf("0 ");
            }
            FOR(i,1,m-n) putchar('9');
            printf(" 1 ");
            FOR(i,1,n) putchar('9');
            puts("");
        }
    }
    return 0;
}
