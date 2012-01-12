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

long long n, ln, nn;

void update(ll a, ll b, ll c) {
    ln = max(ln, (a+1)*(b+2)*(c+2) - a*b*c);
    nn = min(nn, (a+1)*(b+2)*(c+2) - a*b*c);
}

void solve(ll s, ll t) {
    for(int i = 1; i*i <= t; i++)
    if (t % i == 0) {
        update(s, i, t / i);
        update(s, t / i, i);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> n;
    ln = -1; nn = 1000111000111000111LL;
    for(int i = 1; i*i <= n; i++)
    if (n % i == 0) {
        solve(i, n / i);
        solve(n / i, i);
    }
    cout << nn << ' ' << ln << endl;
    return 0;
}
