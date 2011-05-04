#pragma comment(linker, "/STACK:16777216")
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
#include <iomanip>

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

pair<int,int> x[100111];
int res[100111];

int ab(int x) {
    if (x < 0) return -x;
    else return x;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, a, b;
    cin >> n >> a >> b;
    if (a == b) {
        FOR(i,1,a) cout << "1 ";
        FOR(i,1,b) cout << "2 ";
        return 0;
    }
    FOR(i,1,n) {
        cin >> x[i].F;
        if (a > b) x[i].S = i;
        else x[i].S = -i;
    }
    sort(x+1, x+n+1);
    
    if (a > b) {
        FOR(i,1,a) res[ab(x[i].S)] = 1;
        FOR(i,a+1,n) res[ab(x[i].S)] = 2;
    }
    else {
        FOR(i,1,b) res[ab(x[i].S)] = 2;
        FOR(i,b+1,n) res[ab(x[i].S)] = 1;
    }
    FOR(i,1,n) cout << res[i] << ' ';
    return 0;
}
