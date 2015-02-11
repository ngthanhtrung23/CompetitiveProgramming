
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

int n, cnt[500111];
string s;

bool isVowel(char c) {
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y';
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> s) {
        n = s.length();
        s = " " + s;
        FOR(i,1,n) {
            cnt[i] = cnt[i-1];
            if (isVowel(s[i])) ++cnt[i];
        }

        long double res = 0.0;
        long long cur = 0;
        int from = 1, to = n;
        bool add = true;
        FOR(len,1,n) {
            if (add) {
                cur += cnt[to] - cnt[from - 1];
                ++from; --to;
                if (from > to) {
                    add = false;
                    --from; ++to;
                }
            }
            else {
                cur -= cnt[from] - cnt[to - 1];
                ++from; --to;
            }
            res += cur / (double) len;
        }
        cout << res << endl;
    }
    return 0;
}
