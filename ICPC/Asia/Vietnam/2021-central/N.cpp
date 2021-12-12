#include "bits/stdc++.h"

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
using namespace std;

#define next kajclajclkjl
int next[26][100111];
int need[26];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);

    string s;
    while (cin >> s) {
        int ls = (int) s.size();

        for (int c = 0; c < 26; c++) {
            next[c][ls] = ls;
            for (int i = ls-1; i >= 0; i--) {
                int cur = s[i] - 'a';
                next[c][i] = cur == c ? i : next[c][i+1];
            }
        }

        string t; cin >> t;
        int lt = (int) t.size();
        memset(need, 0, sizeof need);
        for (char c : t) {
            need[c - 'a']++;
        }

        auto can = [ls](int start, int nChar, int _cur[26]) {
            int cur[26];
            REP(i,26) cur[i] = _cur[i];

            while (nChar--) {
                pair<int,int> smallest = {ls, -1};

                for (int c = 0; c < 26; c++) {
                    if (cur[c]) {
                        smallest = min(smallest, {next[c][start], c});
                    }
                }

                if (smallest.first >= ls) return false;

                cur[smallest.second]--;
                start = next[smallest.second][start] + 1;
            }
            return true;
        };

        if (!can(0, lt, need)) {
            cout << -1 << endl;
            return 0;
        }

        string res = "";
        int start = 0;
        for (int turn = 0; turn < lt; turn++) {
            for (int c = 0; c < 26; c++) {
                if (!need[c]) continue;

                need[c]--;
                if (can(next[c][start] + 1, lt - turn - 1, need)) {
                    res += (char) (c + 'a');
                    start = next[c][start] + 1;
                    break;
                }
                need[c]++;
            }
        }
        cout << res << endl;
    }

    return 0;
}
