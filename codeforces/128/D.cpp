
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

const int MN = 100111;
int n, cnt[MN], a[MN];

bool solve() {
    int nn = *min_element(a+1, a+n+1);
    FOR(i,1,n) a[i] -= nn;
    int ln = *max_element(a+1, a+n+1);

    if (ln >= n) return false;
    if (ln == 0) return false;

    memset(cnt, 0, sizeof cnt);
    FOR(i,1,n) cnt[a[i]]++;

    FOR(i,0,ln) {
        if (cnt[i] == 0) return false;
        --cnt[i];
    }
    FOR(i,1,ln-1) {
        if (cnt[i] == 0) return false;
        --cnt[i];
    }

    FOR(i,0,ln-1) {
        int t = cnt[i];
        if (cnt[i+1] < t) return false;
        cnt[i] -= t;
        cnt[i+1] -= t;
    }
    FOR(i,0,ln) if (cnt[i]) return false;
    return true;
}

bool check(vector<int> x) {
    n = x.size();
    FOR(i,1,n) a[i] = x[i-1];
    return solve();
}

int main() {
    ios :: sync_with_stdio(false);

    // number disconnected
    assert(!check(vector<int> {100, 102, 102}));
    assert(!check(vector<int> {100, 100, 102}));
    // cannot go down
    assert(!check(vector<int> {1, 2, 3, 4}));
    // correct
    assert(check(vector<int> {1, 2, 3, 4, 3, 2}));
    assert(check(vector<int> {1, 2, 1, 2, 1, 2, 3, 4, 3, 2}));
    assert(check(vector<int> {1, 2, 1, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 2, 3, 4, 3, 4, 3, 2}));

    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) cin >> a[i];
        cout << (solve() ? "YES" : "NO") << endl;
    }
    return 0;
}
