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
using namespace std;

const double PI = acos(-1.0);

int cnt[11];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n; scanf("%d", &n);
    while (n--) {
        int u; scanf("%d", &u);
        cnt[u]++;
    }
    int res = 0;
    
    // si = 4 --> ko the nhet them ng khac
    res = cnt[4];
    
    // si = 3 --> nhet them si = 1
    res += cnt[3]; cnt[1] -= cnt[3]; if (cnt[1] < 0) cnt[1] = 0;
    
    // si = 2 --> nhet them si = 2 / 2 * si = 1
    if (cnt[2] % 2 == 0) {
        res += cnt[2] / 2;
        cnt[2] = 0;
    }
    else {
        res += cnt[2] / 2 + 1;
        cnt[2] = 0;
        cnt[1] -= 2; if (cnt[1] < 0) cnt[1] = 0;
    }
    
    // si = 1
    res += (cnt[1] + 3) / 4;
    
    printf("%d", res);
    return 0;
}
