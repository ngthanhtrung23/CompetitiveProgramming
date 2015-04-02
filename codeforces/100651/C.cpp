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

int k, a[55][100111], first[55], last[55], pass[55], res[55], cnt[55];

int main() {
    int ntest = 0;
    cin >> ntest;
    FOR(test,1,ntest) {
        cout << "Case " << test << ":";
        cin >> k;
        FOR(i,1,52) cin >> a[1][i];
        first[1] = 1; last[1] = 52;
        FOR(i,2,k) first[i] = 1, last[i] = 0;

        int idle = 0;
        int total = 52;
        FOR(i,1,k) cnt[i] = 1;
        while (true) {
            ++idle;
            if (idle == 1500) {
                cout << " unwinnable" << endl;
                break;
            }

            FOR(i,1,k) pass[i] = 0;
            FOR(i,1,k) {
                if (first[i] <= last[i]) {
                    if (a[i][first[i]] == cnt[i]) {
                        pass[i] = cnt[i];
                        res[i] = cnt[i];
                        if (i == k) --total;
                        ++first[i];
                    }
                    else {
                        ++last[i];
                        a[i][last[i]] = a[i][first[i]];
                        ++first[i];
                    }
                    ++cnt[i]; if (cnt[i] == 14) cnt[i] = 1;
                }
            }
            FOR(i,1,k-1) if (pass[i]) {
                last[i+1]++;
                a[i+1][last[i+1]] = pass[i];
            }
            if (total == 0) {
                FOR(i,1,k) cout << ' ' << res[i];
                cout << endl;
                break;
            }
        }
    }
    return 0;
}
