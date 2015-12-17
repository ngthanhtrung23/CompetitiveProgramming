#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll unsigned long long
#define SZ(x) ((int) (x).size())
using namespace std;

bool check(string s) {
    bool increasing = true;
    FOR(i,1,SZ(s)) {
        if (s[i] > s[i-1]) {
            if (!increasing) return false;
        }
        else if (s[i] < s[i-1]) {
            if (increasing) increasing = false;
        }
        else {
        }
    }
    return true;
}

ll f[77][11][2][2];

void solve(string bound) {
    int l = SZ(bound);

    FOR(len,1,l-1) FOR(last,0,9) FOR(dir,0,1) FOR(lower,0,1) {
        ll cur = f[len][last][dir][lower];
        if (cur == 0) continue;

        FOR(add,0,9) {
            int dir2 = dir, lower2 = lower;
            if (!lower && add + '0' > bound[len]) continue;
            if (add + '0' < bound[len]) lower2 = 1;

            if (add < last) dir2 = 1;
            if (add > last) {
                if (dir == 1) continue;
            }

            f[len+1][add][dir2][lower2] += cur;
        }
    }
}

ll get(string bound) {
    int l = SZ(bound);
    ll res = 0;

    // less digit
    memset(f, 0, sizeof f);
    FOR(c,1,9) {
        f[1][c][0][1] = 1;
    }
    solve(bound);
    FOR(i,1,l-1) FOR(last,0,9) FOR(dir,0,1) FOR(lower,0,1)
        res += f[i][last][dir][lower];

    // equal digit
    memset(f, 0, sizeof f);
    FOR(c,1,bound[0] - '0') {
        int lower = 0;
        if (c < bound[0] - '0') lower = 1;
        f[1][c][0][lower] = 1;
    }
    solve(bound);
    FOR(last,0,9) FOR(dir,0,1) FOR(lower,0,1)
        res += f[l][last][dir][lower];
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        string bound; cin >> bound;
        if (check(bound)) {
            cout << get(bound) << '\n';
        }
        else cout << -1 << '\n';
        cout << endl;
    }
}
