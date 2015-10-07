
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int n, t;
string a, b;
char s[100111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> t) {
        cin >> a >> b;

        int cnt_diff = 0;
        REP(i,n) {
            if (a[i] != b[i]) {
                ++cnt_diff;
            }
        }
        int A = 0, B = 0, C = 0;
        if (cnt_diff >= t) {
            A = B = cnt_diff - t;
            C = cnt_diff - A - B;
            if (C < 0) {
                puts("-1");
                continue;
            }
        }
        else {
            A = B = 0;
            C = cnt_diff;
        }

        int diff_a = 0, diff_b = 0;
        REP(i,n) {
            if (a[i] != b[i]) {
                if (A > 0) s[i] = a[i], --A;
                else if (B > 0) s[i] = b[i], --B;
                else if (C > 0) {
                    s[i] = 'a';
                    while (s[i] == a[i] || s[i] == b[i]) ++s[i];
                    --C;
                }
                if (s[i] != a[i]) ++diff_a;
                if (s[i] != b[i]) ++diff_b;
            }
        }
        REP(i,n) {
            if (a[i] == b[i]) {
                if (diff_a < t) {
                    s[i] = 'a';
                    while (s[i] == a[i]) ++s[i];
                    ++diff_a; ++diff_b;
                }
                else s[i] = a[i];
            }
        }

        if (diff_a != t || diff_b != t) {
            puts("-1");
            continue;
        }
        puts(s);
    }
}
