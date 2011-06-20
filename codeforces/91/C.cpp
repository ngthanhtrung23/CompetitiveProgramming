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
const int BASE = 1000000009;

int n, m, lab[100111], res = 0;

int getRoot(int u) {
    if (lab[u] < 0) return u;
    else return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[u] = x;
        lab[v] = u;
    }
    else {
        lab[v] = x;
        lab[u] = v;
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d %d", &n, &m);
    
    FOR(i,1,n) lab[i] = -1;
    
    res = 0;
    int u, v;
    while (m--) {
        scanf("%d %d", &u, &v);
        u = getRoot(u); v = getRoot(v);
        if (u != v) {
            merge(u,v);
            u = getRoot(u);
        }
        else {
            res = (res + res + 1) % BASE;
        }
        printf("%d\n", res);
    }
    return 0;
}
