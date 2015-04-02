
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

int l, r, d, len;
bool isPrime[10111], used[1011];
int res[1011];

void init() {
    isPrime[1] = false;
    FOR(n,2,10000) {
        isPrime[n] = true;
        for(int i=2; i*i <= n; ++i)
            if (n % i == 0) {
                isPrime[n] = false;
                break;
            }
    }
}

bool hasSol;
void attempt(int pos) {
    if (hasSol) return ;
    if (pos > len) {
        hasSol = true;
        return ;
    }
    FOR(val,l,r) if (!used[val]) {
        used[val] = true;
        res[pos] = val;

        int from = pos - 1, sum = val;
        bool can = true;
        FOR(dd,2,d) {
            if (from < 1) break;
            sum += res[from];
            --from;
            if (isPrime[sum]) {
                can = false;
                break;
            }
        }
        if (can) attempt(pos+1);
        if (hasSol) return ;

        used[val] = false;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    init();
    while (cin >> l >> r >> d && l) {
        memset(used, false, sizeof used);
        len = r - l + 1;
        hasSol = false;
        attempt(1);
        if (hasSol) {
            FOR(i,1,len-1) cout << res[i] << ','; cout << res[len] << '\n';
        }
        else {
            cout << "No anti-prime sequence exists.\n";
        }
    }
    return 0;
}
