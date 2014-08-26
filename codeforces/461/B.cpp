#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const long long MOD = 1000000007;
const int MN = 100111;

long long f[2][MN];
vector<int> ke[MN];
int n, col[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
    memset(f, 0, sizeof f);
}

void dfs(int u) {
    if (ke[u].size() == 0) {
        if (col[u] == 0) {
            f[0][u] = 1;
            f[1][u] = 0;
        } else {
            f[0][u] = 0;
            f[1][u] = 1;
        }
        return ;
    }

    vector<long long> f0;
    vector<long long> f1;
    vector<long long> left, right;

    int k = ke[u].size();
    f0.resize(k);
    f1.resize(k);
    left.resize(k);
    right.resize(k);

    REP(i,k) {
        int v = ke[u][i];
        dfs(v);

        f0[i] = f[0][v];
        f1[i] = f[1][v];
    }

    REP(i,k) {
        if (i == 0) {
            left[i] = (f0[i] + f1[i]) % MOD;
        } else {
            left[i] = (left[i-1] * f0[i] + left[i-1] * f1[i]) % MOD;
        }
    }
    FORD(i,k-1,0) {
        if (i == k-1) {
            right[i] = (f0[i] + f1[i]) % MOD;
        } else {
            right[i] = (right[i+1] * (f0[i] + f1[i])) % MOD;
        }
    }

    if (col[u] == 0) {
        f[0][u] = left[k-1];
        REP(i,k) {
            f[1][u] = (f[1][u] 
                    + f1[i] 
                    * ((i > 0) ? left[i-1] : 1) % MOD
                    * ((i < k-1) ? right[i+1] : 1)) % MOD;
        }
    } else {
        f[0][u] = 0;
        f[1][u] = left[k-1];
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        init();
        FOR(i,2,n) {
            int fi;
            cin >> fi;
            ++fi;
            ke[fi].push_back(i);
        }
        FOR(i,1,n) cin >> col[i];

        dfs(1);

        cout << f[1][1] << endl;
    }
    return 0;
}
