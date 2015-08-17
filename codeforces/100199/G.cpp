
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
using namespace std;

const int MN = 100111;

int n, f[MN];
pair< pair<int,int>, int > a[MN];

int main() {
    ios :: sync_with_stdio(false);
    freopen("people.in", "r", stdin);
    freopen("people.out", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].first.first >> a[i].first.second;
            a[i].first.second = -a[i].first.second;
            a[i].second = i;
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) a[i].first.second = -a[i].first.second;

        vector<int> h(n+5, 1e9 + 7);
//        FOR(i,1,n) cout << a[i].first.second << ' '; cout << endl;
        FOR(i,1,n) {
            int cur = lower_bound(h.begin(), h.end(), a[i].first.second) - h.begin();
            f[i] = cur + 1;
            h[cur] = a[i].first.second;
//            PR0(h, n);
        }
        int res = *max_element(f+1, f+n+1);
        cout << res << endl;

        int last = 1e9 + 7;
        vector<int> trace;
        FORD(i,n,1) if (f[i] == res && last > a[i].first.second) {
            last = a[i].first.second;
            --res;
            trace.push_back(a[i].second);
        }
        for(int x : trace) cout << x << ' '; cout << endl;
    }
}
