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
int a[22];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int k; cin >> k;
    FOR(i,1,12) cin >> a[i];
    sort(a+1, a+13);
    int res = 0;
    int now = 12;
    while (k > 0) {
        if (now == 0) {
            puts("-1");
            return 0;
        }
        k -= a[now];
        now--;
        res++;
    }
    cout << res;
    return 0;
}
