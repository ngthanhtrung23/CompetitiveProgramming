
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

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        deque<int> a, b;
        int x; cin >> x; while (x--) { int u; cin >> u; a.push_back(u); }
        int y; cin >> y; while (y--) { int u; cin >> u; b.push_back(u); }

        bool ok = false;
        FOR(turn,1,1000111) {
            x = a.front(); a.pop_front();
            y = b.front(); b.pop_front();

            if (x > y) { a.push_back(y); a.push_back(x); }
            else { b.push_back(x); b.push_back(y); }

            if (a.empty()) {
                cout << turn << ' ' << 2 << endl;
                ok = true;
                break;
            }
            else if (b.empty()) {
                cout << turn << ' ' << 1 << endl;
                ok = true;
                break;
            }
        }
        if (!ok) cout << -1 << endl;
    }
    return 0;
}
