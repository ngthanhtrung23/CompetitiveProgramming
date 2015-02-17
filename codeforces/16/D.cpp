
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

int n, a[111];
char tmp[100111];

int main() {
    while (scanf("%d\n", &n) == 1) {
        FOR(i,1,n) {
            int h, m;
            char c;
            scanf("[%d:%d %c", &h, &m, &c);
            if (h == 12) h = 0;
            gets(tmp);

            int t = h * 60 + m;
            if (c == 'p') t += 12 * 60;

            a[i] = t;
        }

//        PR(a, n);

        int res = 0, equal = 0;

        FOR(i,1,n) {
            if (i == 1) {
                res = 1;
                equal = 1;
            }
            else {
                if (a[i] > a[i-1]) {
                    equal = 1;
                }
                else if (a[i] < a[i-1]) {
                    ++res;
                    equal = 1;
                }
                else {
                    equal++;
                    if (equal > 10) {
                        ++res;
                        equal = 1;
                    }
                }
            }
        }

        cout << res << endl;
    }
    return 0;
}

