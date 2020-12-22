#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

const int MOD = 998244353;

const int RED = 0;
const int BLACK = 1;

struct Good {
    int pos;
    int color;
} goods[55];

bool operator < (const Good& a, const Good& b) {
    return a.pos < b.pos;
}

int bads[55];
int fact[111];
int nGood, nBad;

vector<int> getInRange(int l, int r) {
    vector<int> res;
    res.push_back(l);
    
    FOR(i,1,nBad) {
        if (l <= bads[i] && bads[i] <= r) {
            res.push_back(bads[i]);
        }
    }

    res.push_back(r);
    return res;
}

// f[i][j][color_i][color_j][diff]
// = how many ways to color all points in [i, j]
//   color_i = color of i
//   color_j = color of j
//   diff = number of red points - number of black points
int f[55][55][2][2][211];

#define next kajkcjlasjc
// combined[diff] = how many ways to combine all f, diff = number of red - number of black
// next = temporary array to calculate combined
int combined[211], next[211];

// C(n, k)
int C[1011][1011];

int32_t main() {
    ios::sync_with_stdio(0);

    FOR(i,0,1000) {
        C[i][0] = 1;
        FOR(j,1,i) C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
    }

    cin >> nGood >> nBad;
    FOR(i,1,nGood) {
        cin >> goods[i].pos;
        string s; cin >> s;
        if (s[0] == 'R') goods[i].color = RED;
        else goods[i].color = BLACK;
    }
    FOR(i,1,nBad) cin >> bads[i];
    sort(goods + 1, goods + nGood + 1);
    sort(bads + 1, bads + nBad + 1);

    fact[0] = 1;
    FOR(i,1,100) fact[i] = fact[i-1] * i % MOD;

    if (nGood == 1) {
        if (goods[1].color == RED) {
            cout << fact[nBad] << endl;
        } else {
            cout << 0 << endl;
        }
        return 0;
    }

    assert(nGood >= 2);
    const int ZERO = 100;

    // before 1 & after N
    const int INF = 1e9 + 11;
    auto before = SZ(getInRange(-INF, goods[1].pos)) - 1;
    auto after = SZ(getInRange(goods[nGood].pos, INF)) - 2;

    int red = 0, black = 0;
    if (goods[1].color == RED) {
        red += before;
    } else {
        black += before;
    }
    if (goods[nGood].color == RED) {
        red += after;
    } else {
        black += after;
    }

    /*
    DEBUG(before);
    DEBUG(after);
    DEBUG(red);
    DEBUG(black);
    */

    combined[ZERO + red - black] = fact[before - 1] * fact[after] % MOD * C[before - 1 + after][before - 1] % MOD;
    /*
    DEBUG(ZERO + red - black);
    DEBUG(combined[goods[1].color][ZERO + red - black]);
    */

    int total = before + after - 1;

    FOR(cur_range,1,nGood - 1) {
        int l = goods[cur_range].pos;
        int r = goods[cur_range+1].pos;
        int cl = goods[cur_range].color;
        int cr = goods[cur_range + 1].color;

        vector<int> cur = getInRange(l, r);

        memset(f, 0, sizeof f);
        FOR(len,1,SZ(cur)-1) {
            FOR(i,0,SZ(cur)-1-len) {
                int j = i + len;
                assert(j < SZ(cur));

                REP(ci,2) REP(cj,2) {
                    if (len == 1) {
                        int diff = ZERO;
                        if (ci == RED) ++diff; else --diff;
                        if (cj == RED) ++diff; else --diff;

                        /*
                        if (i == 0 && ci != cl) continue;
                        if (j == SZ(cur)-1 && cj != cr) continue;
                        */

                        f[i][i+1][ci][cj][diff] = 1;
                    } else {
                        FOR(k,i+1,j-1) {
                            int ck = (cur[k] - cur[i] <= cur[j] - cur[k]) ? ci : cj;

                            int len1 = k - i + 1;
                            int len2 = j - k + 1;

                            FOR(diff1,ZERO-len1,ZERO+len1) {
                                int f1 = f[i][k][ci][ck][diff1];
                                if (f1 == 0) continue;

                                FOR(diff2,ZERO-len2,ZERO+len2) {
                                    int f2 = f[k][j][ck][cj][diff2];
                                    if (f2 == 0) continue;

                                    int diff = diff1 + diff2 - ZERO;
                                    // ck counted twice
                                    if (ck == RED) --diff;
                                    if (ck == BLACK) ++diff;

                                    f[i][j][ci][cj][diff] = (f[i][j][ci][cj][diff] + f1 * f2 % MOD * C[j-i-2][k-i-1]) % MOD;
                                }
                            }
                        }
                    }
                }
            }
        }
        // done f

        total += SZ(cur) - 2;
        FOR(diff1,ZERO-100,ZERO+100) FOR(diff2,ZERO-100,ZERO+100) {
            int f1 = combined[diff1];
            if (f1 == 0) continue;

            int f2 = f[0][SZ(cur)-1][cl][cr][diff2];
            if (f2 == 0) continue;

            int diff = diff1 + diff2 - ZERO;
            if (cl == RED) --diff;
            if (cl == BLACK) ++diff;

            next[diff] = (next[diff] + (f1 * f2) % MOD * C[total][SZ(cur) - 2]) % MOD;
        }

        FOR(d,0,200) {
            combined[d] = next[d];
        }
        memset(next, 0, sizeof next);
    }
    int res = 0;
    FOR(d,ZERO+1,ZERO+100) res = (res + combined[d]) % MOD;
    cout << res << endl;

    return 0;
}

