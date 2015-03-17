
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

const int MN = 200111;
char s[MN], t[MN];
int ls, lt, k;
const char c[] = {'A', 'C', 'G', 'T'};
bitset<200011> good[4], result;

int sum[MN];

int main() {
    while (scanf("%d%d%d\n", &ls, &lt, &k) == 3) {
        gets(s);
        gets(t);

        REP(turn,4) {
            memset(sum, 0, sizeof sum);
            good[turn].reset();
            REP(i,ls) if (s[i] == c[turn]) {
                int l = max(0, i - k);
                int r = min(ls, i + k + 1);
                sum[l] += 1;
                sum[r] -= 1;
            }
            REP(i,ls) {
                if (i) sum[i] += sum[i-1];
                if (sum[i]) good[turn].set(i);
            }
        }
        result.reset();
        REP(i,ls) result.set(i);

        REP(i,lt) {
            switch (t[i]) {
                case 'A': result &= good[0] >> i; break;
                case 'C': result &= good[1] >> i; break;
                case 'G': result &= good[2] >> i; break;
                case 'T': result &= good[3] >> i; break;
            }
        }
        int res = 0;
        REP(i,ls) {
            if (result.test(i)) ++res;
        }
        cout << res << endl;
    }
    return 0;
}
