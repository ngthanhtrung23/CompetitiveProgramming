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

ll n;
const int prime[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
const int bound[12] = {10,7,3,2,1,1,1,1,1,1,1,1};
int greatest[12];
ll power[12][20];

ll res, best;

void attempt(int i, ll prod, ll div) {
    if (i == 12) {
        if (div > best || (div == best && res > prod)) {
            best = div;
            res = prod;
        }
        return ;
    }
    FORD(x,bound[i],0)
    if (prod <= n / power[i][x])
    if (i == 11 || div * greatest[i+1] * (x+1) >= best) {
        attempt(i+1, prod * power[i][x], div * (x+1));
    }
}

int main() {
    freopen("divisors.in", "r", stdin);
    freopen("divisors.out", "w", stdout);
    
    REP(i,12) {
        power[i][0] = 1;
        FOR(p,1,bound[i]) power[i][p] = power[i][p-1] * prime[i];
    }
    
    greatest[11] = 2;
    FORD(i,10,0) greatest[i] = greatest[i+1] * (bound[i]+1);
    
    while (cin >> n) {
        res = 1; best = 1;
        attempt(0, 1, 1);
        cout << res << endl;
    }
    return 0;
}
