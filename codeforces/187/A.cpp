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
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const int MN = 200111;

int a[MN], b[MN], ind[MN];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,1,n) {
            scanf("%d", &b[i]);
            ind[b[i]] = i;
        }
        FOR(i,1,n) a[i] = ind[a[i]];
        int can = 1;
        while (can < n && a[can+1] > a[can]) ++can;
        cout << n - can << endl;
    }
    return 0;
}
