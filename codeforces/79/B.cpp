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

pair<int,int> a[1011];
int m, n, k, t;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> m >> n >> k >> t;
    FOR(i,1,k) scanf("%d %d", &a[i].F, &a[i].S);
    sort(a+1, a+k+1);
    
    FOR(i,1,t) {
        int u, v;
        scanf("%d %d", &u, &v);
        int x = lower_bound(a+1, a+k+1, MP(u,v)) - a;
        if (a[x] == MP(u,v)) puts("Waste");
        else {
            int d = (u-1)*n+v;
            d -= x-1;
            if (d % 3 == 1) puts("Carrots");
            else if (d % 3 == 2) puts("Kiwis");
            else puts("Grapes");
        }
    }
    return 0;
}
