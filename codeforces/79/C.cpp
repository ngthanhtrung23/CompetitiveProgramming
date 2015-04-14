
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

string s, b[111];
vector<int> lefts[100111];
int best, save;

void update(int i, int j) {
    int len = j - i + 1;
    if (len > best) {
        best = len;
        save = i;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s) {
        int n; cin >> n;
        FOR(i,1,n) cin >> b[i];

        REP(i,s.length()) lefts[i].clear();

        multiset<int> bounds;
        REP(i,s.length()) {
            FOR(j,1,n)
                if (b[j].length() <= s.length()-i && s.substr(i, b[j].length()) == b[j]) {
                    bounds.insert(i + b[j].length()-1);
                    lefts[i].push_back(i + b[j].length()-1);
                }
        }

        best = 0, save = 0;
        REP(i,s.length()) {
            if (bounds.empty()) {
                int j = s.length() - 1;
                update(i, j);
            }
            else {
                int j = *bounds.begin() - 1;
                update(i, j);
            }

            for(auto x : lefts[i])
                bounds.erase(bounds.find(x));
        }
        cout << best << ' ' << save << endl;
    }
    return 0;
}
