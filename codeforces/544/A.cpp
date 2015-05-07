
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
    string s;
    int n;
    while (cin >> n >> s) {
        bool appear[300];
        memset(appear, false, sizeof appear);
        string cur = "";
        vector<string> res;
        for(char c : s) {
            if (!appear[c]) {
                if (!res.empty()) res.back() += cur;
                cur = "";
                string tmp = ""; tmp += c;
                res.push_back(tmp);

                appear[c] = true;
            }
            else cur += c;
        }
        if (!res.empty()) res.back() += cur;

        if (res.size() < n) cout << "NO" << endl;
        else {
            cout << "YES" << endl;
            REP(i,n) {
                if (i) cout << endl;
                cout << res[i];
            }
            FOR(i,n,res.size()-1) cout << res[i];
            cout << endl;
        }
    }
    return 0;
}
