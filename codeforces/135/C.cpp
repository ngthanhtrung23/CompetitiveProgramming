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

char s[100111];

bool can[10];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    gets(s);
    int cur0 = 0, cur1 = 0;
    int n = strlen(s), t0, t1;
    
    if (n % 2 == 0) {
        t0 = t1 = (n - 2) / 2;
    }
    else {
        t1 = (n - 2 + 1) / 2;
        t0 = n - 2 - t1;
    }
    
    REP(i,n) {
        if (s[i] == '0') cur0++;
        else if (s[i] == '1') cur1++;
    }
    
    // Try all 0
    int l0 = cur0 - t0, l1 = cur1 - t1;
    REP(i,n) if (s[i] == '?') l0++;
    
    if (l0 > l1) can[0] = true;
    
    // Try all 1
    l0 = cur0 - t0; l1 = cur1 - t1;
    REP(i,n) if (s[i] == '?') l1++;
    if (l1 > l0) can[3] = true;
    
    // Last == 0 ?
    l0 = cur0 - t0; l1 = cur1 - t1;
    if (s[n-1] == '0' || s[n-1] == '?') {
        bool mark = false;
        if (s[n-1] == '?') {
            l0++;
            s[n-1] = '0';
            mark = true;
        }
        REP(i,n) if (s[i] == '?') {
            if (l0 < l1) l0++;
            else l1++;
        }
        if (mark) {
            s[n-1] = '?';
        }
        if (l0 == l1) can[2] = true;
    }
    
    // Last == 1 ?
    l0 = cur0 - t0; l1 = cur1 - t1;
    if (s[n-1] == '1' || s[n-1] == '?') {
        bool mark = false;
        if (s[n-1] == '?') {
            l1++;
            s[n-1] = '1';
            mark = true;
        }
        
        REP(i,n) if (s[i] == '?') {
            if (l0 < l1) l0++;
            else l1++;
        }
        
        if (mark) {
            s[n-1] = '?';
        }
        if (l0 == l1) can[1] = true;
    }
    
    if (can[0]) puts("00");
    if (can[1]) puts("01");
    if (can[2]) puts("10");
    if (can[3]) puts("11");
    return 0;
}
