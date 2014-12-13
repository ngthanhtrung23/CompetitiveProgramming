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

string s;
int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        vector<int> res;
        int sum = 0;
        bool ok = true;
        REP(i,s.length()) {
            if (s[i] == '(') ++sum;
            if (s[i] == ')') --sum;
            if (s[i] == '#') {
                --sum;
                res.push_back(1);
            }
            if (sum < 0) ok = false;
        }
        if (sum < 0 || !ok) {
            cout << -1 << endl;
        }
        else {
            if (sum && !res.size()) cout << -1 << endl;
            else {
                if (sum) res[SZ(res)-1] += sum;
                int cur = 0, sum = 0;
                ok = true;
                REP(i,s.length()) {
                    if (s[i] == '(') ++sum;
                    if (s[i] == ')') --sum;
                    if (s[i] == '#') sum -= res[cur++];
                    if (sum < 0) ok = false;
                }
                if (ok && sum == 0) {
                    for(int x : res) cout << x << endl;
                }
                else cout << -1 << endl;
            }
        }
    }
    return 0;
}
