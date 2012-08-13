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

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << "'" << a[_] << "' "; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

int n, l;
string s[1011];

int main() {
    while (getline(cin, s[n+1])) ++n;

    FOR(i,1,n) l = max(l, (int) s[i].length());
    FOR(i,1,l+2) putchar('*'); puts("");
    int turn = 0, Left, Right;
    FOR(i,1,n) {
        putchar('*');
        int need = l - s[i].length();
        Left = need / 2;
        if (need % 2) {
            if (turn == 1) ++Left;
            turn = 1 - turn;
        }
        Right = need - Left;
        FOR(x,1,Left) putchar(' ');
        printf("%s", s[i].c_str());
        FOR(x,1,Right) putchar(' ');
        puts("*");
    }
    FOR(i,1,l+2) putchar('*'); puts("");
    return 0;
}
