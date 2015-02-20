
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

int n;
char a[111][111];

bool solve1() {
    FOR(i,1,n) {
        int sum = 0;
        FOR(j,1,n) sum += a[i][j];
        if (sum == (int) ('E') * n) return false;
    }
    FOR(i,1,n) {
        FOR(j,1,n) if (a[i][j] != 'E') {
            cout << i << ' ' << j << endl;
            break;
        }
    }
    return true;
}

bool solve2() {
    FOR(j,1,n) {
        int sum = 0;
        FOR(i,1,n) sum += a[i][j];
        if (sum == (int) ('E') * n) return false;
    }
    FOR(j,1,n) {
        FOR(i,1,n) if (a[i][j] != 'E') {
            cout << i << ' ' << j << endl;
            break;
        }
    }
    return true;
}

int main() {
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];

        if (!solve1())
            if (!solve2())
                cout << -1 << endl;
    }
    return 0;
}
