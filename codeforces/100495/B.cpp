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

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        set<string> s;
        int n, q; cin >> n >> q;
        FOR(i,1,n) {
            string cur; cin >> cur;
            if (cur.size() > 2) {
                sort(cur.begin()+1, cur.end()-1);
            }
            s.insert(cur);
        }
        cout << "Case #" << test << ": ";
        while (q--) {
            string cur; cin >> cur;
            if (cur.size() > 2) {
                sort(cur.begin()+1, cur.end()-1);
            }
            if (s.count(cur)) cout << 1; else cout << 0;
        }
        cout << endl;
    }
    return 0;
}
