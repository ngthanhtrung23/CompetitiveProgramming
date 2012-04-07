//#pragma comment(linker, "/STACK:66777216")
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
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

char s[1100111];

bool check() {
    int first = 0, l = strlen(s);
    while (first < l && s[first] == ' ') first++;
    return s[first] == '#';
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    bool br = true;
    while (gets(s)) {
        if (check()) {
            if (!br) puts("");
            REP(i,strlen(s)) putchar(s[i]);
            puts("");
            br = true;
        }
        else {
            br = false;
            REP(i,strlen(s)) if (s[i] != ' ') putchar(s[i]);
        }
    }
    if (!br) puts("");
    return 0;
}
