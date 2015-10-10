#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int a[2222][2222];

int main()
{
  ios::sync_with_stdio(0);
  freopen("bandits.in", "r", stdin);
  freopen("bandits.out", "w", stdout);

  int n, m;
  while (cin >> n >> m) {
    assert(1 <= n && n <= 2000);
    assert(1 <= m && m <= 2000);

    memset(a, 0, sizeof a);
    a[1][1] = m;
    for (int i = 2; i <= n; i++)
    {
      vector < pair<int,int> > b;
      for (int j = 1; j < i; j++)
        b.emplace_back(a[i - 1][j], j);
      sort(b.begin(), b.end());

      int need = i / 2, sum = 0;
      for (int j = 0; j < need; j++)
        sum += b[j].first + 1;

      if (sum > m)
      {
        a[i][i] = -1;
        for (int j = 1; j < i; j++)
          a[i][j] = a[i - 1][j];
      }
      else
      {
        a[i][i] = m - sum;
        bool ok = true;
        if (need < i && b[need].first == b[need-1].first) {
          ok = false;
        }
        for (int j = 0; j < need; j++) {
          if (ok || b[j].first + 1 <= b[need].first)
            a[i][b[j].second] = b[j].first + 1;
        }
      }
//      PR(a[i], i);
    }

    cout << a[n][n] << endl;
  }
}
