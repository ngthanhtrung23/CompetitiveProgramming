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

int g[100111], f[100111], sum[100111], mark[100111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    memset(f, -1, sizeof f);
    
    int n; cin >> n;
    FOR(i,3,n) {
        FOR(k,2,500) {
            if (k * (k+1) / 2 > i) break;
            int tmp = i + (k-1)*k/2;
            if (tmp % k == 0) {
                int u = tmp / k;
                if (u < k || u > i) continue;
                int now = sum[u] ^ sum[u-k];
                mark[now] = 1;
                if (!now && f[i] == -1) f[i] = k;
            }
        }
        
        g[i] = 0;
        while (mark[g[i]]) g[i]++;
        sum[i] = sum[i-1] ^ g[i];
        
        FOR(k,2,500) {
            if (k * (k+1) / 2 > i) break;
            int tmp = i + (k-1)*k/2;
            if (tmp % k == 0) {
                int u = tmp / k;
                if (u < k || u > i) continue;
                int now = sum[u] ^ sum[u-k];
                mark[now] = 0;
            }
        }
    }
    
    cout << f[n] << endl;
    return 0;
}