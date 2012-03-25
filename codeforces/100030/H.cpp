//#pragma comment(linker, "/STACK:66777216")
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
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

char s[100111];
int n;
int mark[300];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int k;
    while (scanf("%d\n", &k) == 1) {
        gets(s); n = strlen(s);
        memset(mark, false, sizeof mark);
        int j = 0, cur = 0;
        int res = -100, savei, savej;
        REP(i,n) {
            if (!mark[s[i]]) cur++;
            
            mark[s[i]]++;
            while (cur > k) {
                mark[s[j]]--;
                if (!mark[s[j]]) cur--;
                j++;
            }
            if (i-j > res) {
                res = i-j;
                savei = i;
                savej = j;
            }
        }
        printf("%d %d\n", savej + 1, savei + 1);
    }
    return 0;
}
