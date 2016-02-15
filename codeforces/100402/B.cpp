
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 555;
string s[MN];
int n;

int minmove(vector<string> s) {
    int n = SZ(s);
    int x, y, i, j, u, v; // x is the smallest string before string y
    for (x = 0, y = 1; y < n; ++ y) {
        i = u = x;
        j = v = y;
        while (s[i] == s[j]) {
            ++ u; ++ v;
            if (++ i == n) i = 0;
            if (++ j == n) j = 0;
            if (i == x) break; // All strings are equal
        }
        if (s[i] <= s[j]) y = v;
        else {
            x = y;
            if (u > y) y = u;
        }
    }
    return x;
}

vector<string> best, cur;

string rots[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    cin >> s[0];
    n = SZ(s[0]);
    FOR(i,1,n-1) cin >> s[i];

    REP(j,n) {
        REP(i,n) rots[j] += s[i][j];
    }
//    REP(i,n) DEBUG(s[i]);
//    REP(j,n) DEBUG(rots[j]);


    REP(j,n) {
        vector<string> all;
        REP(i,n) {
            all.push_back(s[i].substr(j) + s[i].substr(0, j));
        }
//        DEBUG(j);
//        for(auto s : all) cout << s << ' '; cout << endl;
        int i = minmove(all);

        cur.clear();
        for(int turn = 0, ii = i; turn < n; ++turn, ii = (ii + 1) % n) {
            cur.push_back(all[ii]);
        }
        if (j == 0 || cur < best) best = cur;
    }
    for(auto s : best) cout << s << '\n';
    cout << endl;
}
