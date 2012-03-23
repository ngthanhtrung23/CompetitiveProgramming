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

int a[511];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, x;
    while (scanf("%d%d", &n, &x) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);
        sort(a+1, a+n+1);
        int first = -1, last = -1, res = 0;
        if (x < a[1]) {
            first = last = 1;
            n++;
            res++;
        }
        else if (x > a[n]) {
            n++;
            res++;
            first = last = n;
        }
        else {
            FOR(i,1,n) if (a[i] == x) {
                if (first == -1) {
                    first = last = i;
                }
                else {
                    last = i;
                }
            }
            if (first == -1) {
                n++;
                res++;
                a[n] = x;
            }
            sort(a+1, a+n+1);
            FOR(i,1,n) if (a[i] == x) {
                if (first == -1) {
                    first = last = i;
                }
                else {
                    last = i;
                }
            }
        }
        int mid = (n + 1) / 2;
        if (first <= mid && mid <= last) {
            printf("%d\n", res);
            continue;
        }
    //    cout << first << ' ' << last << endl;
    //    cout << n << ' ' << res << ' ' << mid << endl;
        while (mid < first || last < mid) {
            res++;
            last++; n++;
            mid = (n + 1) / 2;
        }
        printf("%d\n", res);
    }
    return 0;
}
