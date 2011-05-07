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

vector<int> s[222*222];
bool mark[222], c[222][222], exist[222];
int n, m;

int a[222], na, b[222], nb;

void init() {
    FOR(i,1,m) FOR(j,1,m) if (exist[i] && exist[j]) c[i][j] = 1;
    
    FOR(i,1,n) {
        memset(mark, 0, sizeof mark);
        REP(x,s[i].size()) mark[s[i][x]] = 1;
        
        na = 0; nb = 0;
        FOR(j,1,m) if (exist[j] && mark[j]) a[++na] = j;
        FOR(k,1,m) if (exist[k] && !mark[k]) b[++nb] = k;
        
        FOR(j,1,na)
        FOR(k,1,nb)
            c[a[j]][b[k]] = 0;
    }
}

int qu[222], dd[222];

void bfs(int start) {
    int first = 1, last = 1; qu[1] = start;
    dd[start] = 1;
    while (first <= last) {
        int u = qu[first++];
        FOR(v,1,m)
        if (c[u][v] && !dd[v]) {
            qu[++last] = v;
            dd[v] = 1;
        }
    }
    
    cout << last;
    FOR(i,1,last) cout << ' ' << qu[i];
    cout << endl;
}

void solve() {
    FOR(i,1,m)
    if (!dd[i] && exist[i]) {
        bfs(i);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    n = n*(n-1)/2;
    FOR(i,1,n) {
        int k; scanf("%d", &k);
        while (k--) {
            int u; scanf("%d", &u);
            s[i].PB(u);
            m = max(m, u);
            exist[u] = 1;
        }
    }
    if (n == 1) {
        cout << "1 " << s[1][0] << endl;
        cout << s[1].size()-1;
        FOR(i,1,s[1].size()-1) {
            cout << ' ' << s[1][i];
        }
        cout << endl;
        return 0;
    }
    init();
    solve();
    return 0;
}
