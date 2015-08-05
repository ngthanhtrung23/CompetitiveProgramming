
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

pair<int,int> a[100111];
pair<int,int> res[100111];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].first;
            a[i].second = i;
        }
        sort(a+1, a+n+1);

        FOR(i,1,n) {
            int u = a[i].second;
        
            if (u == 1) res[u].first = a[i+1].first - a[i].first;
            else if (u == n) res[u].first = a[i].first - a[i-1].first;
            else res[u].first = min(a[i+1].first - a[i].first, a[i].first - a[i-1].first);

            res[u].second = max(a[i].first - a[1].first, a[n].first - a[i].first);
        }

        FOR(i,1,n) printf("%d %d\n", res[i].first, res[i].second);
    }
}
