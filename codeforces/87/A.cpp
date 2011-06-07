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

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

pair<ll,int> all[2000111];
ll cntA, cntB;
int cnt;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    ll a, b; cin >> a >> b;
    ll x = a * b / gcd(a, b);
    
    FOR(i,1,x/a-1) all[cnt++] = MP(a * i, 0);
    FOR(i,1,x/b-1) all[cnt++] = MP(b * i, 1);
    sort(all, all+cnt);
    
    ll last = 0;
    REP(i,cnt) {
        if (all[i].S == 0) cntA += all[i].F - last;
        else cntB += all[i].F - last;
        
        last = all[i].F;
    }
    if (a > b) cntA += x - last; else cntB += x - last;
    if (cntA > cntB) puts("Dasha");
    else if (cntA < cntB) puts("Masha");
    else puts("Equal");
    
    return 0;
}
