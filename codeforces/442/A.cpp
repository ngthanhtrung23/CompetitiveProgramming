#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int n, cur[111];
string a[111];

#define TWO(x) (1<<(x))

int get(int mask, char c) {
    if (c >= '1' && c <= '5') {
        return mask & (1<<(c-'1'));
    }
    else if (c == 'R') return mask & (1<<5);
    else if (c == 'G') return mask & (1<<6);
    else if (c == 'B') return mask & (1<<7);
    else if (c == 'Y') return mask & (1<<8);
    else return mask & (1<<9);
}

bool check(int mask) {
    FOR(i,1,n) {
        cur[i] = 0;
        REP(t,2) {
            char c = a[i][t];
            cur[i] += get(mask, c);
        }
    }

    FOR(i,1,n) FOR(j,i+1,n)
        if (a[i] != a[j] && cur[i] == cur[j]) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        int res = 1000111000;
        REP(mask,TWO(10)) {
            if (check(mask)) res = min(res, __builtin_popcount(mask));
        }
        cout << res << endl;
    }
    return 0;
}
