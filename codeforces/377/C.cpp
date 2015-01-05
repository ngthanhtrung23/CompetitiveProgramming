#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

#define move _move
using namespace std;

int a[111];
pair<char,int> move[22];
int f[TWO(20)], m;

int get(int mask) {
    if (f[mask] > -1000111000) return f[mask];
    if (mask == TWO(m) - 1) return f[mask] = 0;

    int i = __builtin_popcount(mask) + 1;
    int res;

    if (move[i].first == 'p') {
        REP(x,m)
            if (!CONTAIN(mask,x)) {
                if (move[i].second == 1) res = a[x+1] + get(mask + TWO(x));
                else res = -a[x+1] + get(mask + TWO(x));
                break;
            }
    }
    else {
        if (move[i].second == 1) {
            res = -1000111000;
            REP(x,m)
                if (!CONTAIN(mask,x)) {
                    res = max(res, get(mask + TWO(x)));
                }
        }
        else {
            res = 1000111000;
            REP(x,m)
                if (!CONTAIN(mask,x)) {
                    res = min(res, get(mask + TWO(x)));
                }
        }
    }

    return f[mask] = res;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1, greater<int>());
        cin >> m;
        FOR(i,1,m) cin >> move[i].first >> move[i].second;

        REP(i,TWO(m)) f[i] = -1000111000;
        cout << get(0) << endl;
    }
    return 0;
}

