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

int n, top;
char a[30111], st[30111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        top = 0;

        int l = 1, r = n;
        FOR(turn,1,n) {
            if (a[l] < a[r]) {
                st[++top] = a[l];
                ++l;
            } else if (a[l] > a[r]) {
                st[++top] = a[r];
                --r;
            } else {
                int ll = l, rr = r;
                while (a[ll] == a[rr] && ll+1 <= rr-1) {
                    ++ll;
                    --rr;
                }

                if (a[ll] <= a[rr]) {
                    st[++top] = a[l];
                    ++l;
                } else {
                    st[++top] = a[r];
                    --r;
                }
            }
        }

        int draw = 0;
        FOR(i,1,n) {
            cout << st[i];
            ++draw;
            if (draw == 80) {
                cout << "\n";
                draw = 0;
            }
        }
        cout << endl;
    }
    return 0;
}
