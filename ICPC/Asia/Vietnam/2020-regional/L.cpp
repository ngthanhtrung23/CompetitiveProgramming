#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = '" << (_X) << "'" << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

int f[20][20][20][20][3][2][2];
int p10[20];

const int INF = 1e18;

void initF() {
    REP(i,20) REP(mx,20) REP(my,20) REP(mz,20)
        REP(carry,3) REP(ab,2) REP(bc,2)
            f[i][mx][my][mz][carry][ab][bc] = INF;
    f[0][0][0][0][0][1][1] = 0;
}

vector<vector<int>> getNext(string s) {

    vector<vector<int>> next(SZ(s), vector<int> (10, 0));
    // next(i, next_digit)
    // = currently matched i characters
    //   we add next_digit.
    //   How many characters match?

    REP(i,SZ(s)) FOR(next_digit,0,9) {
        // We already matched the whole string.
        if (i == SZ(s) - 1) {
            next[i][next_digit] = SZ(s) - 1;
            continue;
        }

        string cur = s.substr(1, i);  // remember s[0] = ' '
        cur += (char) ('0' + next_digit);

        next[i][next_digit] = 0;  // worst case: do not match anything.
        FORD(res, i+1, 1) {
            string s_pref = s.substr(1, res);
            string cur_suf = cur.substr(SZ(cur) - res, res);

            if (s_pref == cur_suf) {
                next[i][next_digit] = res;
                break;
            }
        }
    }
    return next;
}

void upMin(int& f, int val) {
    if (val < f) f = val;
}

int solve(string n, string x, string y, string z) {
    auto next_x = getNext(x);
    auto next_y = getNext(y);
    auto next_z = getNext(z);

    initF();

    auto cmp = [] (int da, int db, int a_leq_b) -> int {
        if (da == db) return a_leq_b;

        if (da < db) return 1;
        return 0;
    };

    FOR(i,0,15) REP(match_x,SZ(x)) REP(match_y,SZ(y)) REP(match_z,SZ(z))
        FOR(carry,0,2) FOR(a_leq_b,0,1) FOR(b_leq_c,0,1) {
            int cur = f[i][match_x][match_y][match_z][carry][a_leq_b][b_leq_c];
            if (cur == INF) continue;

            FOR(da,0,9) FOR(db,0,9) {
                int dc = (n[i+1] - '0' - da - db - carry) % 10;
                if (dc < 0) dc += 10;
                assert((da + db + dc + carry) % 10 == n[i+1] - '0');

                int new_match_x = next_x[match_x][da];
                int new_match_y = next_y[match_y][db];
                int new_match_z = next_z[match_z][dc];
                int new_carry = (da + db + dc + carry) / 10;

                int new_a_leq_b = cmp(da, db, a_leq_b);
                int new_b_leq_c = cmp(db, dc, b_leq_c);

                upMin(
                        f[i+1][new_match_x][new_match_y][new_match_z][new_carry][new_a_leq_b][new_b_leq_c],
                        cur + p10[i] * (dc - da));
            }
        }

    return f[16][SZ(x) - 1][SZ(y) - 1][SZ(z) - 1][0][1][1];
}

int32_t main() {
    ios::sync_with_stdio(0);

    p10[0] = 1;
    FOR(i,1,16) p10[i] = p10[i-1] * 10;

    string n;
    cin >> n;
    reverse(ALL(n));
    while (SZ(n) < 16) n += '0';
    n = " " + n;

    vector<string> need(3);
    REP(i,3) {
        cin >> need[i];
        reverse(ALL(need[i]));
        need[i] = " " + need[i];
    }

    sort(ALL(need));
    int res = INF;

    do {
        int cur = solve(n, need[0], need[1], need[2]);
        upMin(res, cur);
    } while (next_permutation(ALL(need)));

    if (res == INF) cout << -1 << endl;
    else cout << res << endl;

    return 0;
}

