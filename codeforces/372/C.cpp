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

const int MN = 150111;

long long f[2][MN];
// f[i][j] = maximum value, if after i-th launch, we stand at position j
int n, m, d;
int a[311], b[311], t[311];
int qu[MN], first, last;

void add(int cur, int x) {
    while (first <= last && f[1-cur][ qu[last] ] <= f[1-cur][x]) {
        --last;
    }
    qu[++last] = x;
}

int main() {
    while (cin >> n >> m >> d) {
        long long sumb = 0;
        FOR(i,1,m) {
            cin >> a[i] >> b[i] >> t[i];
            sumb += b[i];
        }
        memset(f, 0, sizeof f);

        FOR(i,1,m) {
            int cur = i % 2;
            long long can = (t[i] - t[i-1]) * (long long) d;
            if (can > n) can = n;

            first = 1, last = 0;
            FOR(x,1,min((int) can+1,n)) add(cur, x);

            FOR(j,1,n) {
                while (first <= last && qu[first] + can < j) ++first;
                f[cur][j] = f[1-cur][ qu[first] ] - abs(a[i] - j);

                if (j + can + 1 <= n) add(cur, j + can + 1);
            }
        }
        cout << ((*max_element(f[m%2]+1, f[m%2]+n+1)) + sumb) << endl;
    }
    return 0;
}

