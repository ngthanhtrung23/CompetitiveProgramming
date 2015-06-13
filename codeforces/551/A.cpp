
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

int n;
pair<int,int> a[2011];
int res[2011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].first;
            a[i].second = i;
        }
        sort(a+1, a+n+1);
        reverse(a+1, a+n+1);

        FOR(i,1,n) {
            if (a[i].first == a[i-1].first) res[ a[i].second ] = res[ a[i-1].second ];
            else res[ a[i].second ] = i;
        }
        FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}

