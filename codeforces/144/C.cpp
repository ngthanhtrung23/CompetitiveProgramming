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

char a[100111], b[100111];
int cnt[2][30][100111], s[100111];
int m, n;

bool check(int i) {
    int last = i + n - 1;
    int has;
    
    if (i) has = s[last] - s[i-1];
    else has = s[last];
    
    FOR(c,'a','z') {
        int na = cnt[1][c-'a'][last];
        if (i) na -= cnt[1][c-'a'][i-1];
        
        int nb = cnt[0][c-'a'][n-1];
        
//        if (i == 1 || i == 5) cout << c << ' ' << na << ' ' << nb << ' ' << has << endl;
        
        if (na > nb) return false;
        if (na < nb) {
            has -= (nb - na);
            if (has < 0) return false;
        }
    }
    return true;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    gets(a); gets(b);
    m = strlen(a), n = strlen(b);
    
    REP(i,n) {
        FOR(c,'a','z') {
            if (i) cnt[0][c-'a'][i] = cnt[0][c-'a'][i-1];
        }
        cnt[0][b[i]-'a'][i]++;
    }
    
    REP(i,m) {
        FOR(c,'a','z') {
            if (i) cnt[1][c-'a'][i] = cnt[1][c-'a'][i-1];
        }
        if (i) s[i] = s[i-1];
        if (a[i] == '?') s[i]++;
        else cnt[1][a[i]-'a'][i]++;
    }
    
    int res = 0;
    REP(i,m-n+1) if (check(i)) {
        res++;
    }
    printf("%d", res);
    return 0;
}
