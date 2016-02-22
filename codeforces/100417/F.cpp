#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > rounds;

int main()
{
  freopen("factor.in", "r", stdin);
  freopen("factor.out", "w", stdout);
  int n, m, x;
  cin >> n;
  vector <int> a;
  for (int i = 0; i < n * 2; i++)
    a.push_back(i + 1);

  for (int i = 0; i < n * 2; i++)
  {
    rounds.push_back(a);
    rotate(a.begin() + 1, a.end() - 1, a.end());
  }

  cin >> m;
  int used = 0;
  while (m--)
  {
    cin >> x;
    for (int i = 0; i < x; i++)
      for (int j = 0; j < n; j++)
        cout << rounds[used + i][j] << ' ' << rounds[used + i][n * 2 - 1 - j] << endl;
    if (m) cout << endl;
    used += x;
  }
}