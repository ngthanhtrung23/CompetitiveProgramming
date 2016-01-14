
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

const int MN = 100111;
int cnt[33];
int n;

void append(string& s, int i, int t) {
    char c = 'a' + i - 1;
    REP(i,t) s += c;
}

bool allEvenDivisible(int x) {
    FOR(i,1,n) if (cnt[i] % 2 == 0 && cnt[i] % x) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        int nOdd = 0;
        FOR(i,1,n) {
            cin >> cnt[i];
            if (cnt[i] % 2) ++nOdd;
        }
        string res = "";
        int best = 0;
        if (nOdd >= 2) {
            FOR(i,1,n) {
                append(res, i, cnt[i]);
            }
        }
        else if (nOdd == 1) {
            int all = 1;
            int x = 0, odd = -1;
            FOR(i,1,n) if (cnt[i] % 2) {
                x = cnt[i];
                odd = i;
            }

            FOR(nGroup,1,x) if (x % nGroup == 0) {
                if (allEvenDivisible(nGroup)) {
                    best = nGroup;
                }
            }

            FOR(turn,1,best) {
                FOR(i,1,n) if (cnt[i] % 2 == 0) append(res, i, cnt[i] / 2 / best);
                FORD(i,n,1) if (cnt[i] % 2 == 0) append(res, i, cnt[i] / 2 / best);
                append(res, odd, x / best);
            }
        }
        else {
            FOR(good,1,n) {
                string cur = "";
                int x = cnt[good];

                int cur_best = 0;
                FOR(nGroup,1,x) if (x % (nGroup*2) == 0) {
                    bool can = true;
                    FOR(i,1,n) if (i != good) {
                        if (cnt[i] % (2*nGroup)) can = false;
                    }
                    if (can) cur_best = nGroup;
                }

                if (cur_best > best) {
                    best = cur_best;
                    res = "";
                    FOR(turn,1,best) {
                        FOR(i,1,n) if (i != good) append(res, i, cnt[i] / 2 / best);
                        FORD(i,n,1) if (i != good) append(res, i, cnt[i] / 2 / best);
                        append(res, good, x / best);
                    }
                }
            }
            best *= 2;
        }
        printf("%d\n", best);
        puts(res.c_str());
    }
}
