
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

char cur;

int get(int a, int b, bool print, int& wrong) {
    if (a > b) swap(a, b);
    // now a <= b
    if (a == 0) {
        if (b == 1) return 0;
        return -1000111000;
    }
    int res = b / a + get(a, b % a, print, wrong);
    wrong += b / a - 1;
    if (print) {
        REP(turn,b/a) {
            cout << cur;
            if (a == 1 && turn == 0) cur = 'B' + 'T' - cur;
        }
        cur = 'T' + 'B' - cur;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    int n, r;
    while (cin >> n >> r) {
        if (n == 1 && r == 1) {
            cout << 0 << endl << 'T' << endl;
            continue;
        }
        int res = 1000111000, save = -1;
        FOR(i,1,r-1) {
            int cur_wrong = 0;
            if (get(i, r, false, cur_wrong) == n) {
                if (cur_wrong < res) {
                    res = cur_wrong;
                    save = i;
                }
            }
        }
        if (save < 0) cout << "IMPOSSIBLE" << endl;
        else {
            cout << -1+res << endl;
            cur = 'T';
            int t;
            get(save, r, true, t);
            cout << endl;
        }
    }
    return 0;
}

