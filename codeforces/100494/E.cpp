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

const int oo = 1000111000;
int N, B, H, W;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> N >> B >> H >> W) {
        int res = oo;

        FOR(i,1,H) {
            int price; cin >> price;
            FOR(choice,1,W) {
                int bed; cin >> bed;

                if (bed >= N && N * price <= B) {
                    res = min(res, N * price);
                }
            }
        }

        if (res == oo) cout << "stay home" << endl;
        else cout << res << endl;
    }
    return 0;
}
