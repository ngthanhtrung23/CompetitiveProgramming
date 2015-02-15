
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

const int MOD = 1e9 + 7;
typedef pair<long long, long long> pll;

pll val[600111], power[600111];
int n[2];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    power[0] = make_pair(1, 1);
    FOR(i,1,600000) {
        power[i].first = power[i-1].first * 5;
        power[i].second = (power[i-1].second * 5) % MOD;
    }
    while (cin >> n[0] >> n[1]) {
        set< pll > all;
        while (n[0]--) {
            string s; cin >> s;
            pll hash = make_pair(0, 0);
            REP(i,s.size()) {
                val[i].first = (s[i] - 'a' + 1) * power[i].first;
                val[i].second = (s[i] - 'a' + 1) * power[i].second % MOD;

                hash.first = hash.first + val[i].first;
                hash.second = (hash.second + val[i].second) % MOD;
            }

            REP(i,s.size()) FOR(to,'a','c') if (to != s[i]) {
                pll cur = make_pair(
                        (to - 'a' + 1) * power[i].first,
                        (to - 'a' + 1) * power[i].second % MOD
                        );
                all.insert(make_pair(
                            hash.first - val[i].first + cur.first,
                            (hash.second - val[i].second + MOD + cur.second) % MOD));
            }
        }
        while (n[1]--) {
            string s; cin >> s;
            pll hash = make_pair(0, 0);
            REP(i,s.size()) {
                hash.first = hash.first + (s[i] - 'a' + 1) * power[i].first;
                hash.second = (hash.second + (s[i] - 'a' + 1) * power[i].second) % MOD;
            }
            cout << (all.count(hash) ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}

