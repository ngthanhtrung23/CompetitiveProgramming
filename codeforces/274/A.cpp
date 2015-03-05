
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

int a[100111];

int main() {
    int n, k;
    while (scanf("%d%d", &n, &k) == 2) {
        set<int> s;
        FOR(i,1,n) scanf("%d", &a[i]);
        sort(a+1, a+n+1);

        FOR(i,1,n) {
            if (a[i] % k) s.insert(a[i]);
            else if (!s.count(a[i] / k)) s.insert(a[i]);
        }
        cout << s.size() << endl;
    }
    return 0;
}

