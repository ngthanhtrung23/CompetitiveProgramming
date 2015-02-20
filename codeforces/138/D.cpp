
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

int m, n;
char a[22][22];
int f[2][44][44][44][44];

int get(int t, int minSum, int maxSum, int minDiff, int maxDiff) {
    if (minSum > maxSum || minDiff > maxDiff) return 0;
    if (f[t][minSum][maxSum][minDiff][maxDiff] >= 0)
        return f[t][minSum][maxSum][minDiff][maxDiff];

    unordered_set<int> s;
    FOR(i,1,m) FOR(j,1,n)
        if ((i+j) % 2 == t) {
            int sum = i+j, diff = i-j+n;
            if (minSum <= sum && sum <= maxSum
                    && minDiff <= diff && diff <= maxDiff) {
                if (a[i][j] == 'R') {
                    int x = get(t, minSum, maxSum, minDiff, diff-1);
                    int y = get(t, minSum, maxSum, diff+1, maxDiff);
                    s.insert(x ^ y);
                }
                if (a[i][j] == 'L') {
                    int x = get(t, minSum, sum-1, minDiff, maxDiff);
                    int y = get(t, sum+1, maxSum, minDiff, maxDiff);
                    s.insert(x ^ y);
                }
                if (a[i][j] == 'X') {
                    int x = get(t, minSum, sum-1, minDiff, diff-1);
                    int y = get(t, minSum, sum-1, diff+1, maxDiff);
                    int z = get(t, sum+1, maxSum, minDiff, diff-1);
                    int w = get(t, sum+1, maxSum, diff+1, maxDiff);

                    s.insert(x ^ y ^ z ^ w);
                }
            }
        }

    int res = 0;
    while (s.count(res)) ++res;
    return f[t][minSum][maxSum][minDiff][maxDiff] = res;
}

int main() {
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        memset(f, -1, sizeof f);
        int res = get(0, 1, m+n, 1, m+n)
                ^ get(1, 1, m+n, 1, m+n);
        if (res) cout << "WIN"; else cout << "LOSE";
        cout << endl;
    }
    return 0;
}

