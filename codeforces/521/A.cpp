
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

int main() {
    int cnt[4];
    int n; string s;
    while (cin >> n >> s) {
        memset(cnt, 0, sizeof cnt);
        for(char c : s) {
            if (c == 'A') ++cnt[0];
            else if (c == 'C') ++cnt[1];
            else if (c == 'G') ++cnt[2];
            else ++cnt[3];
        }
        int nbest = 0, ln = *max_element(cnt, cnt+4);
        REP(i,4) if (cnt[i] == ln) ++nbest;

        long long res = 1;
        FOR(i,1,n) res = (res * nbest) % (int) (1e9 + 7);
        cout << res << endl;
    }
    return 0;
}

