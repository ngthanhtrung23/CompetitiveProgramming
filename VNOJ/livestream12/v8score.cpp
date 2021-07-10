#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int S, nProblem, nJudge;
int scores[22][22];  // [judge][problem]
int f[22][222][222];  // f[i][last_score][sum]
int res[22];

int can(int i, int last_score, int sum) {
    if (i == 1) {
        return last_score == sum;
    }
    if (f[i][last_score][sum] >= 0) return f[i][last_score][sum];

    for (int judge = 1; judge <= nJudge; judge++) {
        int prev_score = scores[judge][i - 1];
        if (prev_score > last_score) continue;

        if (can(i - 1, prev_score, sum - last_score)) {
            return f[i][last_score][sum] = 1;
        }
    }

    return f[i][last_score][sum] = 0;
}

// trace(i, last_score, sum):
// - assumption: can(i, last_score, sum) == true
void trace(int i, int last_score, int sum) {
    assert(can(i, last_score, sum));
    res[i] = last_score;
    if (i == 1) return;

    for (int judge = 1; judge <= nJudge; judge++) {
        int prev_score = scores[judge][i - 1];
        if (prev_score > last_score) continue;

        if (can(i - 1, prev_score, sum - last_score)) {
            trace(i - 1, prev_score, sum - last_score);
            return;
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    // read input
    cin >> S >> nProblem >> nJudge;
    for (int i = 1; i <= nJudge; i++) {
        for (int j = 1; j <= nProblem; j++) {
            cin >> scores[i][j];
        }
    }

    memset(f, -1, sizeof f);
    for (int judge = 1; judge <= nJudge; judge++) {
        int last_score = scores[judge][nProblem];

        if (can(nProblem, last_score, S)) {
            cout << "YES" << endl;
            trace(nProblem, last_score, S);
            for (int i = 1; i <= nProblem; i++) {
                cout << res[i] << ' ';
            }
            cout << endl;
            return 0;
        }
    }

    cout << "NO" << endl;
    return 0;
}
