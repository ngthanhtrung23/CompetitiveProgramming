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
    while (ntest--) {
        string s; cin >> s;
        vector< pair<int,int> > res;
        FOR(row,1,s.length()) if (s.length() % row == 0) {
            int col = s.length() / row;

            REP(j,col) {
                bool ok = true;
                REP(i,row) {
                    int id = i * col + j;
                    if (s[id] != 'X') {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    res.push_back(make_pair(row, col));
                    break;
                }
            }
        }
        cout << res.size();
        for(pair<int,int> p : res) cout << ' ' << p.first << 'x' << p.second;
        cout << endl;
    }
    return 0;
}
