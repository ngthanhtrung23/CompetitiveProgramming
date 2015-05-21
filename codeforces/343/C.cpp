
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

int na, nb;
long long a[MN], b[MN];

bool check(long long val) {
    int j = 0;
    FOR(i,1,na) {
        long long can = val;
        long long pos = a[i];

        if (b[j+1] < pos) {
            if (llabs(pos - b[j+1]) > can) return false;
            long long start = b[j+1];

            while (j < nb && b[j+1] < pos) ++j;
            while (j < nb && min(llabs(b[j+1] - pos), llabs(start - pos)) + llabs(start - b[j+1]) <= can) ++j;

            if (j == nb) return true;
        }
        else {
            while (j < nb && pos + can >= b[j+1]) ++j;
            if (j == nb) return true;
        }
    }
    return j == nb;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> na >> nb) {
        FOR(i,1,na) cin >> a[i];
        FOR(i,1,nb) cin >> b[i];

        long long l = 0, r = 100011100011LL;
        long long res = r;
        while (l <= r) {
            long long mid = (l + r) / 2;
            if (check(mid)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << res << endl;
    }
    return 0;
}
