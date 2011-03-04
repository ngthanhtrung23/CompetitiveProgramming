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
const int MN = 200111;

char s[MN], a[MN];
int Left[30][MN], Right[30][MN], k;

void init() {
    memset(Left, -1, sizeof Left);
    memset(Right, -1, sizeof Right);
    REP(i,k)
    if (i) {
        REP(c,30) {
            Left[c][i] = Left[c][i-1];
            if (s[i-1]-'a' == c) Left[c][i] = i-1;
        }
    }
    FORD(i,k-2,0) {
        REP(c,30) {
            Right[c][i] = Right[c][i+1];
            if (s[i+1]-'a' == c) Right[c][i] = i+1;
        }
    }
}

int ab(int x) {
    if (x < 0) return -x;
    else return x;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d %d\n", &n, &k);
    gets(s);
    init();
    while (n--) {
        gets(a);
        int l = strlen(a);
        ll sum = 0;
        int j, u, v, ii;
        REP(i,l) {
            if (a[i] == s[i]) sum += 0;
            else {
                ii = i;
                if (ii >= k) ii = k-1;
                if (a[i] == s[ii]) sum += ab(i-ii);
                else {
                    u = Left[a[i]-'a'][ii];
                    v = Right[a[i]-'a'][ii];
                    if (u == -1 && v == -1) sum += l;
                    else if (u == -1) sum += ab(v-i);
                    else if (v == -1) sum += ab(u-i);
                    else sum += min(ab(v-i), ab(u-i));
                }
            }
        }
        cout << sum << endl;
    }
    return 0;
}
