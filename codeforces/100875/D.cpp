
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 20;
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int n, a[MN][MN], f[TWO(16)], best[MN], worst[MN];

void go(int mask); 

void update(int i, int pos) {
    best[i] = min(best[i], pos);
    worst[i] = max(worst[i], pos);
}

void play(int mask, int winner, int lose_pos) {
    if (mask == 0) {
        go(winner);
        return ;
    }

    REP(i,n) if (CONTAIN(mask,i)) {
        REP(j,n) if (CONTAIN(mask,j) && i != j) {
            int winner2 = winner;
            if (a[i][j]) {
                winner2 |= TWO(i);
                update(j, lose_pos);
            }
            else {
                winner2 |= TWO(j);
                update(i, lose_pos);
            }

            play(mask - TWO(i) - TWO(j), winner2, lose_pos);
        }
        break;
    }
}

int save[MN];

void go(int mask) {
    if (f[mask]) return ;
    f[mask] = 1;

    if (__builtin_popcount(mask) == 1) {
        REP(i,n) if (CONTAIN(mask,i)) {
            update(i, 1);
        }
        return ;
    }
    int remaining = __builtin_popcount(mask);

    play(mask, 0, remaining / 2 + 1);
}

void solve() {
    memset(f, 0, sizeof f);
    REP(i,n) best[i] = n, worst[i] = 0;

    go(TWO(n) - 1);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n;
        REP(i,n) REP(j,n) cin >> a[i][j];
        solve();
        cout << "Case #" << test << ":\n";
        REP(i,n) cout << best[i] << ' ' << worst[i] << '\n';
        cerr << test << endl;
    }
}
