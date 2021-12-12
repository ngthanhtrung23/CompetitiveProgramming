#include "bits/stdc++.h"

#define int long long
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
using namespace std;

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int ntest; cin >> ntest;
    while (ntest--) {
        string s; cin >> s;

        vector<vector<int>> pos(27, vector<int>());
        for (int i = 0; i < (int) s.size(); i++) {
            pos[s[i] - 'a'].push_back(i);
        }

        int res = 0;
        for (int i = 0; i < 27; i++) {
            for (int j = 0; j < (int) pos[i].size(); j++) {
                int x = j == 0 ? 0 : pos[i][j-1] + 1;
                int y = pos[i][j];
                int z = (j+1 == (int) pos[i].size()) 
                    ? s.size() - 1
                    : pos[i][j+1] - 1;

                res += (y - x + 1) * (z - y + 1);
            }
        }
        cout << res << endl;
    }
    return 0;
}
