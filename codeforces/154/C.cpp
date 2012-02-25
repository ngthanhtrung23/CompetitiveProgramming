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

long long p[1000111];
long long h[1000111], h2[1000111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    p[0] = 1; FOR(i,1,n) p[i] = p[i-1] * 29;
    FOR(i,1,n) h2[i] = p[i];
    int u, v;
    while (m--) {
        scanf("%d%d", &u, &v);
        h[u] += p[v];
        h[v] += p[u];
        
        h2[u] += p[v];
        h2[v] += p[u];
    }
    sort(h + 1, h + n + 1);
    sort(h2 + 1, h2 + n + 1);
    
    int i = 1, j = 1;
    long long res = 0;
    while (i <= n) {
        j = i;
        while (j < n && h[j+1] == h[i]) j++;
        res += (j - i) * (j - i + 1LL);
        i = j + 1;
    }
    i = 1; j = 1;
    while (i <= n) {
        j = i;
        while (j < n && h2[j+1] == h2[i]) j++;
        res += (j - i) * (j - i + 1LL);
        i = j + 1;
    }
    cout << res / 2;
    return 0;
}
