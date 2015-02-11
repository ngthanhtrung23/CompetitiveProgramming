
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

int n, sum[333];
string a[333];

bool attempt(int turn, int pos, int len, int sum, bool greater) {
    if (pos == len) {
        return sum == 0 && greater;
    }
    FOR(cur,'0','9')
        if (sum >= cur - '0' && sum <= cur - '0' + 9 * (len - pos - 1)) 
        if (greater || cur >= a[turn-1][pos]) {
            a[turn][pos] = cur;
            if (attempt(turn, pos+1, len, sum - (cur - '0'), greater || cur > a[turn-1][pos]))
                return true;
            a[turn][pos] = ' ';
        }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) cin >> sum[i];
        a[0] = " "; a[0][0] = '0' - 1;
        FOR(i,1,n) {
            a[i] = a[i-1];
            REP(x,a[i].length()) a[i][x] = ' ';

            if (!attempt(i, 0, a[i-1].length(), sum[i], false)) {
                while (true) {
                    a[i] += ' ';
                    if (a[i].length() * 9 < sum[i]) continue;

                    bool done = true;
                    REP(x,a[i].length()) {
                        int cur = (x) ? 0 : 1;
                        while (sum[i] > cur + (a[i].length() - x - 1) * 9) ++cur;
                        if (cur > 9) {
                            done = false;
                            break;
                        }
                        sum[i] -= cur;
                        a[i][x] = cur + '0';
                    }
                    if (done) break;
                }
            }
            cout << a[i] << endl;
        }
    }
    return 0;
}

