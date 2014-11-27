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
    int n, q;
    while (cin >> n >> q && n) {
        set<int> s; FOR(i,1,n) s.insert(i);
        while (q--) {
            int l, r; cin >> l >> r;
            auto from = s.lower_bound(l);
            auto to = s.upper_bound(r);
            s.erase(from, to);

            auto it = s.lower_bound(l);
            if (it == s.begin()) cout << '*' << ' ';
            else {
                --it;
                cout << *it << ' ';
            }
            it = s.upper_bound(r);
            if (it == s.end()) cout << '*' << "\n";
            else cout << *it << "\n";
        }
        cout << '-' << "\n";
    }
    return 0;
}
