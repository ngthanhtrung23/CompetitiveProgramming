#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

#define ll long long

ll A, B, C;

inline ll next(ll x) {
    return (A * x + x % B) % C;
}

const int MN = 20000000;

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    
    while (cin >> A >> B >> C) {
        ll x = 1;
        bool found = false;
        FOR(i,1,MN) {
            x = next(x);
            if (x == 1) {
                cout << i << endl;
                found = true;
                break;
            }
        }
        if (found) continue;

        x = 1;
        ll y = 1;
        FOR(i,1,MN) {
            x = next(x);
            y = next(next(y));
            if (y == x) break;
        }

        x = 1;
        FOR(i,1,MN) {
            x = next(x);
            y = next(y);
            if (x == y) {
                found = true;

                FOR(j,i+1,MN) {
                    y = next(y);

                    if (y == x) {
                        cout << j << endl;
                        break;
                    }
                }
                break;
            }
        }

        if (found) continue;
        cout << -1 << endl;
    }
    return 0;
}
