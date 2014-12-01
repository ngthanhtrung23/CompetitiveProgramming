#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))
int n, a[1011], s[1011];
int tr[1011][TWO(14)], trMask[1011][TWO(14)];
queue< pair<int,int> > qu;

inline void visit(int i, int mask, int oldMask, char dir) {
    if (tr[i][mask] < 0) {
        tr[i][mask] = dir;
        trMask[i][mask] = oldMask;
        qu.push(make_pair(i, mask));
    }
}

void trace(int n, int mask) {
    if (n == 0) return ;
    trace(n-1, trMask[n][mask]);
    cout << (char) tr[n][mask];
}

int ln[TWO(15)];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    REP(i,TWO(15)) {
        REP(bit,16) if (CONTAIN(i,bit)) ln[i] = bit;
    }
    while (ntest--) {
        cin >> n; FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) s[i] = s[i-1] + a[i];

        int u = s[n];
        while (u % 2 == 0) u /= 2;
        if (u > 1) {
            cout << "no" << endl;
            continue;
        }

        while (!qu.empty()) qu.pop();
        qu.push(make_pair(0, 0));
        REP(i,n+1) REP(mask,s[n]+1) tr[i][mask] = -1;
        tr[0][0] = 0;

        while (!qu.empty()) {
            pair<int,int> cur = qu.front(); qu.pop();
            int i = cur.first, mask1 = cur.second;
            int mask2 = s[i] - mask1;
            if (i == n) continue;

            if (i == n && mask1 == s[n]) break;

            if (mask1 == 0) visit(i+1, a[i+1], 0, 'l');
            
            int lowest1 = mask1 & -mask1;
            int lowest2 = mask2 & -mask2;

            if (lowest1 >= a[i+1]) visit(i+1, mask1 + a[i+1], mask1, 'l');

            if (mask2 == 0) {
                int newMask2 = a[i+1];
                if (ln[newMask2] >= ln[mask1]) visit(i+1, mask1 + a[i+1], mask1, 'r');
                else visit(i+1, mask1, mask1, 'r');
            }

            if (lowest2 >= a[i+1]) {
                int newMask2 = mask2 + a[i+1];
                if (ln[newMask2] >= ln[mask1]) visit(i+1, mask1 + TWO(ln[newMask2]), mask1, 'r');
                else visit(i+1, mask1, mask1, 'r');
            }
        }

        if (tr[n][s[n]] < 0) cout << "no";
        else trace(n, s[n]);
        cout << "\n";
    }
    return 0;
}
