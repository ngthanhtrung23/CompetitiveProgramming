
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

int rand16() {
    return rand() & (TWO(16) - 1);
}
int my_rand() {
    return rand16() << 15 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int NSCORE = 6;
const int NPROB = 5;
const int INF = 1000111000;

int n;
int submit[211][11];
int solved[11];

int maxScore[NSCORE];
bool can[11][211][4011][2];

void init() {
    REP(score,NSCORE) FOR(solved,0,n)
    FOR(add,0,4000) {
        can[score][solved][add][0] = can[score][solved][add][1] = 0;

        int a, b, x, y;

        if (score == 5) a = 0;
        else a = 1;

        if (score == 5) b = 1;
        else b = TWO(score+1);

        x = 1;
        y = TWO(score);

        int minAc = ((n + add) * a) / b + 1 - solved;
        if (minAc < 0) minAc = 0;
        int maxAc = ((n + add) * x) / y - solved;
        if (maxAc > add) maxAc = add;

        // overwrite for no-solved problem
        if (solved == 0) {
            if (score == 5) minAc = maxAc = 0;
            else minAc = 1, maxAc = 0;
        }

        if (0 <= minAc && minAc <= maxAc && maxAc <= add) {
            if (minAc == 0) can[score][solved][add][0] = can[score][solved][add][1] = 1;
            else can[score][solved][add][1] = 1;
        }
    }
}

int32_t main() {
    REP(i,NSCORE) maxScore[i] = 500 * (i + 1);

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (cin >> n) {
        init();

        memset(solved, 0, sizeof solved);
        FOR(i,1,n) FOR(j,1,NPROB) {
            cin >> submit[i][j];
            if (submit[i][j] >= 0) solved[j]++;
        }

        int res = INF;
        int score[11];
        REP(s1,NSCORE) REP(s2,NSCORE) REP(s3,NSCORE) REP(s4,NSCORE) REP(s5,NSCORE) {
            score[1] = s1;
            score[2] = s2;
            score[3] = s3;
            score[4] = s4;
            score[5] = s5;

            int sum[3];

            FOR(person,1,2) {
                sum[person] = 0;
                FOR(prob,1,NPROB) {
                    if (submit[person][prob] < 0) continue;

                    int point = maxScore[score[prob]];
                    int delta = point / 250;

                    sum[person] += point - delta * submit[person][prob];
                }
            }
            if (sum[1] <= sum[2]) continue;

            int minAdd = INF;
            FOR(add,0,4000) {
                bool allCan = true;
                FOR(prob,1,NPROB) {
                    int hasSubmit;
                    if (submit[1][prob] >= 0) hasSubmit = 1;
                    else hasSubmit = 0;

                    allCan = allCan && can[score[prob]][solved[prob]][add][hasSubmit];
                }

                if (allCan) {
                    minAdd = add;
                    break;
                }
            }

            res = min(res, minAdd);
        }
        if (res == INF) res = -1;
        cout << res << endl;
    }
    return 0;
}
