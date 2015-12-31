
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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

string s;
int n, r, len;
double q[22];

int unknown_diff_letters[TWO(12)];
int unopened_box[TWO(12)];
set<char> good[TWO(12)];

double prob(int t, int i, int j, int k) {
    return (1.0 - pow(q[t], 1.0 / (k - j + 1))) * j * 1.0 / i
        + pow(q[t], 1.0 / (k - j + 1)) * pow(1.0 - 1.0 / i, i-j);
}

vector<double> f[22][33][TWO(12)], zero;

void go(int turn, int i, int mask) {
    if (!f[turn][i][mask].empty()) return ;
    
    f[turn][i][mask] = zero;

    // guess a correct letter
    double probCorrect = prob(turn, i, unknown_diff_letters[mask], unopened_box[mask]);
    double sum = 0.0;
    for(char c : good[mask]) {
        double p = probCorrect / unknown_diff_letters[mask];
        sum += p;

        int mask2 = mask;
        REP(i,len) if (s[i] == c) mask2 |= TWO(i);

        if (mask2 == TWO(len) - 1) {
            f[turn][i][mask] [turn] += p;
            continue;
        }

        go(turn, i - 1, mask2);

        REP(player,n)
            f[turn][i][mask] [player] += f[turn][i-1][mask2] [player] * p;
    }

    // incorrect guess
    int incorrect = i - unknown_diff_letters[mask];
    if (incorrect > 0) {
        double p = (1.0 - probCorrect);
        sum += p;

        go((turn + 1) % n, i-1, mask);
        REP(player,n)
            f[turn][i][mask] [player] += f[(turn+1) % n][i-1][mask] [player] * p;
    }

    assert(fabs(sum - 1.0) < 1e-6);

//    cout << turn << ' ' << i << ' ' << mask << endl;
//    PR0(f[turn][i][mask], n);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);

    freopen("wheel.in", "r", stdin);
    freopen("wheel.out", "w", stdout);
    while (cin >> n >> r) {
        cin >> s;
        REP(i,n) cin >> q[i];

        len = SZ(s);
        REP(mask,TWO(len)) {
            set<char> unknown;
            int unopened = 0;

            REP(i,len)
                if (!CONTAIN(mask,i)) {
                    unknown.insert(s[i]);
                    ++unopened;
                }
            unknown_diff_letters[mask] = SZ(unknown);
            unopened_box[mask] = unopened;
            good[mask] = unknown;
        }

        REP(turn,n) REP(i,27) REP(mask,TWO(len))
            f[turn][i][mask].clear();

        zero.clear();
        REP(i,n) zero.push_back(0.0);

        go(0, 26, 0);
        cout << f[0][26][0] [r - 1] << endl;
    }
}
