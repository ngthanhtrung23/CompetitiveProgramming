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
using namespace std;

const double PI = acos(-1.0);

int n, a[100111], cnt[11];
bool mark[100111];

void remove(int need, int sl) {
    int now = 0;
    FOR(i,1,n)
    if (a[i] % 3 == need) {
        mark[i] = true;
        ++now;
        if (now == sl) break;
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        bool ok = false;
        memset(cnt, 0, sizeof cnt);
        int sum = 0;
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            if (a[i] == 0) ok = true;
            cnt[a[i] % 3]++;
            sum = (sum + a[i]) % 3;
        }
        if (!ok) {
            puts("-1");
            continue;
        }
        sort(a+1, a+n+1);
        memset(mark, false, sizeof mark);
        if (sum == 1) {
            if (cnt[1]) remove(1,1);
            else remove(2,2);
        }
        else if (sum == 2) {
            if (cnt[2]) remove(2,1);
            else remove(1,2);
        }
        bool has = false;
        FORD(i,n,2) {
            if (!has && a[i] == 0) break;
            if (!mark[i]) {
                putchar(a[i] + '0');
                has = true;
            }
        }
        puts("0");
    }
    return 0;
}
