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

pair<int,int> a[100111];
int team[100111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n; scanf("%d", &n);
    FOR(i,1,n) {
        scanf("%d", &a[i].F);
        a[i].S = i;
    }
    sort(a+1, a+n+1);
    int x = 0, y = 0;
    int i = 0;
    if (n % 2 == 1) {
        i++;
        x = a[1].F;
        team[a[1].S] = 1;
    }
    while (i < n) {
        if (x < y) {
            i++; team[a[i].S] = 2; y += a[i].F;
            i++; team[a[i].S] = 1; x += a[i].F;
        }
        else {
            i++; team[a[i].S] = 1; x += a[i].F;
            i++; team[a[i].S] = 2; y += a[i].F;
        }
    }
    int cnt;
    FOR(t,1,2) {
        cnt = 0;
        FOR(i,1,n) if (team[i] == t) cnt++;
        printf("%d\n", cnt);
        FOR(i,1,n) if (team[i] == t) printf("%d ", i);
        puts("");
    }
    return 0;
}
