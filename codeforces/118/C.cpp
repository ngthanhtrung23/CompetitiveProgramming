
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

int n, k, val[11];
string s, res[11];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k >> s) {
        REP(x,10) {
            res[x] = s;
            val[x] = 0;
            vector< pair<int,int> > a;
            REP(i,n) {
                int ii = i;
                if (x < s[i] - '0') ii = i;
                else ii = n + n + n - i;
                a.push_back(make_pair(abs(x - s[i] + '0'), ii));
            }
            sort(a.begin(), a.end());
            REP(turn,k) {
                val[x] += a[turn].first;
                int i = a[turn].second;
                if (i > n) i = n + n + n - i;
                res[x][i] = '0' + x;
            }
        }
        int best = *min_element(val, val+10);
        string save = "";
        REP(x,10) if (val[x] == best) {
            if (save == "" || save > res[x])
                save = res[x];
        }
        cout << best << endl << save << endl;
    }
    return 0;
}

