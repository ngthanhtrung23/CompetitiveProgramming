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
    string team1, team2;
    while (cin >> team1 >> team2) {
        int q; cin >> q;

        map< pair<char,int>, int > val;
        while (q--) {
            int t, num;
            char typ, color;
            cin >> t >> typ >> num >> color;
            int old = val[make_pair(typ, num)];
            int cur = old + (color == 'y' ? 1 : 2);
            if (old < 2 && cur >= 2) {
                cout << (typ == 'h' ? team1 : team2) << ' ' << num << ' ' << t << endl;
            }
            val[make_pair(typ, num)] = cur;
        }
    }
    return 0;
}
