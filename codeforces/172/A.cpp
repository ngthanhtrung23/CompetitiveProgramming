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

char tmp[33];
int n;
string a[30111];

bool check(int r) {
    string t = a[1].substr(0,r+1);
    FOR(i,1,n) {
        if (a[i].find(t) != 0) return false;
    }
    return true;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d\n", &n) == 1) {
        FOR(i,1,n) {
            gets(tmp);
            a[i] = string(tmp);
        }
        int res = 0;
        while (res < a[1].length() && check(res)) res++;
        printf("%d\n", res);
    }
    return 0;
}
