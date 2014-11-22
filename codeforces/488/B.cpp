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
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(a) { cout << #a << " = " << a << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int n, a[11];

bool check(int x, int y, int z, int t) {
    int a = (x + y + z + t);
    int b = (y + z) * 2;
    int c = (t - x) * 4;
    return a == b && b == c;
}

void print(vector<int> a) {
    cout << "YES" << endl;
    REP(i,a.size()) cout << a[i] << endl;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);
        if (n == 0) {
            print(vector<int> {1, 1, 3, 3});
        }
        else if (n == 1) {
            print(vector<int> {a[1], 3*a[1], 3*a[1]});
        }
        else if (n == 2) {
            if (4*a[1] - a[2] >= 0) print(vector<int> {4*a[1]-a[2], 3*a[1]});
            else cout << "NO" << endl;
        }
        else if (n == 3) {
            bool ok = false;
            FOR(add,1,500*3) {
                if (check(a[1], a[2], a[3], add)
                        || check(a[1], a[2], add, a[3])
                        || check(a[1], add, a[2], a[3])
                        || check(add, a[1], a[2], a[3])) {
                    ok = true;
                    print(vector<int> {add});
                    break;
                }
            }
            if (!ok) cout << "NO" << endl;
        }
        else { // n == 4
            if (check(a[1], a[2], a[3], a[4])) {
                print(vector<int> {});
            }
            else cout << "NO" << endl;
        }
    }
    return 0;
}

