#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int n;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        int l = -2000000000, r = -l;
        FOR(i,1,n) {
            string s, t;
            int u;
            cin >> s >> u >> t;
            if (t == "N") {
                if (s == "<") s = ">=";
                else if (s == ">") s = "<=";
                else if (s == "<=") s = ">";
                else s = "<";
            }

            if (s == "<") r = min(r, u - 1);
            else if (s == ">") l = max(l, u + 1);
            else if (s == "<=") r = min(r, u);
            else l = max(l, u);
        }

        if (l > r) cout << "Impossible" << endl;
        else cout << l << endl;
    }
    return 0;
}
