// Algo:
// - We can estimate the values of players' skills and problems' difficulties.
//   Start with setting all values to 0, then use ternary search to find the
//   values for skills / difficulties that result in highest probabilities for the
//   observed sequences
// - Similarly, we can estimate players' skills assuming they cheat.
// - Finally, we want to find player that has highest
//   P(observed score | cheat) / P(observed score | fair)

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

const int nPlayer = 100;
const int nQuestion = 10000;
bitset<nQuestion> ans[nPlayer];

double diffs[10111];
double skills[111];

double sigmoid(double x) {
    return 1.0 / (1 + exp(-x));
}

double inverse_sigmoid(double y) {
    return log(y / (1.0 - y));
}

const int NQ = 2000;
// If player is fair, and have `skill`, what is probability of observed scores?
double f_player(int player_id, double skill) {
    double sum_log = 0.0;
    REP(i,NQ) {
        double cur = sigmoid(skill - diffs[i]);

        if (ans[player_id][i]) {
            sum_log += log(cur);
        } else {
            sum_log += log(1.0 - cur);
        }
    }
    return sum_log;
}
// If player cheats, and have `skill`, what is probability of observed scores?
double f_cheating_player(int player_id, double skill) {
    double sum_log = 0.0;
    REP(i,NQ) {
        double cur = 0.5 + 0.5 * sigmoid(skill - diffs[i]);

        if (ans[player_id][i]) {
            sum_log += log(cur);
        } else {
            sum_log += log(1.0 - cur);
        }
    }
    return sum_log;
}

// Find player skill given observed scores, assuming player is fair.
double ternary_player(int player_id) {
    double l = -3.0, r = 3.0;
    REP(turn,7) {
        double x1 = (2*l + r) / 3.0;
        double x2 = (2*r + l) / 3.0;

        double y1 = f_player(player_id, x1);
        double y2 = f_player(player_id, x2);

        if (y1 > y2) r = x2;
        else l = x1;
    }
    return (l + r) / 2.0;
}

// Find player skill given observed scores, assuming player cheats.
double ternary_cheating_player(int player_id) {
    double l = -3.0, r = 3.0;
    REP(turn,7) {
        double x1 = (2*l + r) / 3.0;
        double x2 = (2*r + l) / 3.0;

        double y1 = f_cheating_player(player_id, x1);
        double y2 = f_cheating_player(player_id, x2);

        if (y1 > y2) r = x2;
        else l = x1;
    }
    return (l + r) / 2.0;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
double f1[111], f2[111], score[111];

int32_t main() {
    ios::sync_with_stdio(0);

    int ntest; cin >> ntest;
    int p; cin >> p;

    FOR(test,1,ntest) {
        // shuffle the questions, this helps if we use < 10,000 questions to find cheater.
        vector<int> qids(nQuestion);
        REP(i,nQuestion) qids[i] = i;
        shuffle(qids.begin(), qids.end(), rng);

        REP(i,nPlayer) {
            ans[i].reset();

            string s; cin >> s;
            REP(j,nQuestion) {
                ans[i][j] = s[qids[j]] == '1';
            }
        }

        memset(diffs, 0, sizeof diffs);
        memset(skills, 0, sizeof skills);

        // Initialize question difficulty
        REP(i,nQuestion) {
            int correct = 0;
            REP(j,nPlayer) if (ans[j][i]) ++correct;

            // prob_correct = sigmoid(-diff)
            diffs[i] = -inverse_sigmoid(correct / 100.0);
        }

        pair<double, int> res = {-1e9, -1};
        REP(i,nPlayer) {
            double fair_skill = ternary_player(i);
            double cheating_skill = ternary_cheating_player(i);

            f1[i] = f_player(i, fair_skill);
            f2[i] = f_cheating_player(i, cheating_skill);

            res = max(res, make_pair(f2[i] - f1[i], i));
        }

        cout << "Case #" << test << ": " << res.second + 1 << endl;
    }
}
