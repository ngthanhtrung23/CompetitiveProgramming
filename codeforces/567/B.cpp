
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

pair<char,int> a[111];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        set<int> all, before;
        FOR(i,1,n) {
            cin >> a[i].first >> a[i].second;

            if (a[i].first == '+') {
                all.insert(a[i].second);
            }
            else {
                if (all.count(a[i].second)) all.erase(a[i].second);
                else before.insert(a[i].second);
            }
        }
        int res = 0;
        all = before;
        res = all.size();
        FOR(i,1,n) {
            if (a[i].first == '+') {
                all.insert(a[i].second);
                res = max(res, (int) all.size());
            }
            else {
                all.erase(a[i].second);
            }
        }
        cout << res << endl;
    }
}

