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
const int BASE = 1000000007;

int lab[2011];

int power(int x, int k) {
    if (!k) return 1;
    if (k == 1) return x % BASE;
    long long mid = power(x, k >> 1);
    mid = (mid * mid) % BASE;
    if (k & 1) return (mid * x) % BASE;
    else return mid;
}

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    u = getRoot(u); v = getRoot(v);
    if (u == v) return ;
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[u] = x;
        lab[v] = u;
    } else {
        lab[v] = x;
        lab[u] = v;
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    memset(lab, -1, sizeof lab);
    FOR(i,1,n-k+1) {
        int j = i + k - 1;
        int u = i, v = j;
        while (u < v) {
            merge(u, v);
            u++; v--;
        }
    }
    int cnt = 0;
    FOR(i,1,n) if (lab[i] < 0) cnt++;
    cout << power(m, cnt);
    return 0;
}
