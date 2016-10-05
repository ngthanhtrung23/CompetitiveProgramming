
#include <bits/stdc++.h>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) \
  { cout << #X << " = " << (X) << endl; }
#define PR(A, n)                      \
  {                                   \
    cout << #A << " = ";              \
    FOR(_, 1, n) cout << A[_] << ' '; \
    cout << endl;                     \
  }
#define PR0(A, n)                  \
  {                                \
    cout << #A << " = ";           \
    REP(_, n) cout << A[_] << ' '; \
    cout << endl;                  \
  }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

int solve(int k, int a, int b) {
  // First, we simulate the tournament until 1 player left in each half
  int winners = 1 << k;
  int losers = 0;
  int is_winner = 1;
  int round = 0;
  while (winners > 1 || losers > 1) {
    round += 1;
    // winner group
    int drop = winners / 2;
    int just_failed = 0;
    if (is_winner) {
      if (!a) {
        is_winner = 0;
        just_failed = 1;
      } else
        --a;
    }

    // loser group
    if (!is_winner && !just_failed) {
      if (!b) {
        return winners + losers / 2 + 1;
      } else {
        --b;
      }
    }
    losers /= 2;

    assert(losers == drop || losers == 0);
    losers += drop;
    winners -= drop;

    if (round > 1) {
      if (!is_winner) {
        if (!b) {
          return winners + losers / 2 + 1;
        } else {
          --b;
        }
      }
      losers /= 2;
    }
  }

  if (is_winner) {
    if (a + b) return 1;
    return 2;
  } else {
    if (a + b == 2)
      return 1;
    else
      return 2;
  }
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  int ntest;
  cin >> ntest;
  while (ntest--) {
    int k, a, b;
    cin >> k >> a >> b;
    cout << solve(k, a, b) << '\n';
  }
}
