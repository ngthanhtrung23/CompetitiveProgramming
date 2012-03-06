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

int a[100111];
pair<int,int> b[100111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n; ll k;
    while (cin >> n >> k) {
        FOR(i,1,n) scanf("%d", &a[i]);
        sort(a+1, a+n+1);
        int m = 0;
        FOR(i,1,n) if (i == 1 || a[i] != a[i-1]) {
            m++;
            b[m] = MP(a[i], 1);
        }
        else b[m].S++;
        
        FOR(i,1,m) {
            ll cur = b[i].S * (ll) n;
            if (cur >= k) {
                int res = (k + b[i].S - 1) / b[i].S;
                cout << b[i].F << ' ' << a[res] << endl;
                break;
            }
            else {
                k -= cur;
            }
        }
    }
    return 0;
}
