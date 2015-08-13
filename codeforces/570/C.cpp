#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 300111;
int n, q;
string s;

inline int get(int i, int j) {
    if (i > j) swap(i, j);
    return max(j - i - 2, 0);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> q) {
        cin >> s;
        s = " " + s;
        set<int> all;
        all.insert(0);
        all.insert(n+1);

        FOR(i,1,n) if (s[i] != '.') {
            all.insert(i);
        }
        int last = 0, res = 0;
        for(auto p : all) {
            if (p == 0) {
            }
            else {
                res += get(last, p);
                last = p;
            }
        }
        while (q--) {
            int u; char c;
            cin >> u >> c;
            if (c == '.' && s[u] == '.') {
            }
            else if (c != '.' && s[u] != '.') {
            }
            else if (c == '.' && s[u] != '.') {
                auto next = *all.upper_bound(u);
                auto prev = all.lower_bound(u); --prev;

                res -= get(u, next);
                res -= get(*prev, u);
                
                all.erase(u);

                res += get(*prev, next);
            }
            else {
                auto next = *all.upper_bound(u);
                auto prev = all.lower_bound(u); --prev;

                res += get(u, next);
                res += get(*prev, u);

                all.insert(u);
                
                res -= get(*prev, next);
            }
            s[u] = c;

            printf("%d\n", res);
        }
    }
}

