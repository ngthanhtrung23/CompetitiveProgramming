#include <bits/stdc++.h>
using namespace std;
const double oo = 1e15;

int n, s, cnt[11][111], tr[11][111][111], v[11];
double f[11][111][111];

vector<int> trace(int i, int j, int k)
{
  if (!i) return vector<int>();
  int a = tr[i][j][k];
  vector<int> res = trace(i - 1, j - cnt[i][a], k - a);
  res.push_back(a);
  return res;
}

int main()
{
  freopen("elections.in", "r", stdin);
  freopen("elections.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  int x, t, V = 0;
  cin >> n >> s;
  for (int i = 1; i <= n; i++)
  {
    cin >> v[i] >> t;
    V += v[i];
    for (int j = 0; j <= 100; j++)
      cnt[i][j] = j;
    while (t--)
    {
      cin >> x;
      for (int j = x; j <= 100; j++)
        cnt[i][j]--;
    }
  }

  double ans = oo;
  vector <int> bestAs;
  for (int A = s; A <= 100; A++)
  {
    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= s; j++)
        for (int k = 0; k <= A; k++)
          f[i][j][k] = oo;

    f[0][0][0] = 0;

    for (int i = 1; i <= n; i++)
      for (int j = 0; j <= s; j++)
        for (int k = 0; k <= A; k++)
        {
          double cur = f[i - 1][j][k];
          if (cur > oo - 1) 
            continue;
          for (int a = 0; j + cnt[i][a] <= s; a++)
            if (k + a <= A)
            {
              double newF = cur + fabs(1. * v[i] / V - 1. * a / A);
              int jj = cnt[i][a] + j;
              if (f[i][jj][k + a] > newF)
              {
                f[i][jj][k + a] = newF;
                tr[i][jj][k + a] = a;
              }
            }
        }

    if (f[n][s][A] < ans)
    {
      ans = f[n][s][A];
      bestAs = trace(n, s, A);
    }
  }

  for (auto x : bestAs)
    cout << x << endl;
}