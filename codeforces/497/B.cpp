#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
int sum[2][MN], a[MN], n;

int get(int t) {
    int i = 0;
    int win[2], lastwin = -1; win[0] = win[1] = 0;
    while (i < n) {
        if (sum[0][n] - sum[0][i] < t && sum[1][n] - sum[1][i] < t) return -1;

        int l = i+1, r = n, res = n;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (sum[0][mid] - sum[0][i] >= t || sum[1][mid] - sum[1][i] >= t) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }

        if (sum[0][res] - sum[0][i] == t) ++win[0], lastwin = 0;
        else ++win[1], lastwin = 1;
        i = res;
    }
    if (win[0] == win[1]) return -1;
    if (win[lastwin] != max(win[0], win[1])) return -1;
    else return max(win[0], win[1]);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i]; --a[i];
            sum[0][i] = sum[0][i-1];
            sum[1][i] = sum[1][i-1];
            sum[a[i]][i] += 1;
        }
//        PR(sum[0], n);
//        PR(sum[1], n);

        vector< pair<int,int> > res;
        FOR(t,1,n) {
            int s = get(t);
            if (s > 0)
                res.push_back(make_pair(s, t));
        }
        cout << res.size() << endl;
        sort(res.begin(), res.end());
        for(auto e : res)
            cout << e.first << ' ' << e.second << endl;
    }
    return 0;
}
