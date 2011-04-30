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

char s[100111], a[11][20];
vector<int> ke[100111];
int n, L;

inline bool check(int left, int right, int k) {
    int l = strlen(a[k]);
    int now = left;
    REP(i,l) {
        if (a[k][i] != s[now]) return false;
        now++;
    }
    return true;
}

void match(int left) {
    FOR(i,1,n) {
        int l = strlen(a[i]);
        int right = left + l - 1;
        if (right >= L) continue;
        if (check(left, right, i)) {
//            cout << left << ' ' << right << endl;
            ke[left].PB(right);
        }
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    gets(s);
    scanf("%d\n", &n);
    FOR(i,1,n) gets(a[i]);
    
    L = strlen(s);
    REP(i,L) {
        match(i);
    }
    
    int right = L-1, best = 0, save = 0;
    FORD(i,L-1,0) {
        REP(x,ke[i].size()) {
            int u = ke[i][x];
            right = min(right, u-1);
        }
        if (right - i + 1 > best) {
            best = right - i + 1;
            save = i;
        }
    }
    cout << best << ' ' << save << endl;
    return 0;
}
