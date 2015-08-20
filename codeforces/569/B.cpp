
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
int n, a[MN], b[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        set<int> appear;
        FOR(i,1,n) {
            if (a[i] >= 1 && a[i] <= n && !appear.count(a[i])) {
                appear.insert(a[i]);
                b[i] = a[i];
            }
            else b[i] = 0;
        }
        set<int> available;
        FOR(i,1,n) if (!appear.count(i)) available.insert(i);
        FOR(i,1,n) if (!b[i]) {
            b[i] = *available.begin();
            available.erase(b[i]);
        }
        FOR(i,1,n) printf("%d ", b[i]); puts("");
    }
}
