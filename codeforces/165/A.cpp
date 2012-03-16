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

pair<int,int> a[1011];
int n;

bool check1(int i) {
    FOR(j,1,n) if (j != i)
        if (a[j].F > a[i].F && a[j].S == a[i].S) return true;
    return false;
}

bool check2(int i) {
    FOR(j,1,n) if (j != i)
        if (a[j].F < a[i].F && a[j].S == a[i].S) return true;
    return false;
}

bool check3(int i) {
    FOR(j,1,n) if (j != i)
        if (a[j].F == a[i].F && a[j].S < a[i].S) return true;
    return false;
}

bool check4(int i) {
    FOR(j,1,n) if (j != i)
        if (a[j].F == a[i].F && a[j].S > a[i].S) return true;
    return false;
}

bool check(int i) {
    return check1(i) && check2(i) && check3(i) && check4(i);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    int res = 0;
    FOR(i,1,n) scanf("%d%d", &a[i].F, &a[i].S);
    FOR(i,1,n) {
        if (check(i)) {
            res++;
        }
    }
    cout << res;
    return 0;
}
