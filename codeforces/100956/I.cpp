#include <bits/stdc++.h>
using namespace std;

int n, col[22222], id[6666];
vector <int> b[6666];

int isGood(int i)
{
  int sum = 0;
  for (auto j : b[i])
    sum += col[j] - 1;
  return sum > n * (n / 2 - 1);
}

int isGood(int u, int v)
{
  int intersect = 0;
  for (int i = 0, j = 0; i < b[u].size() && j < b[v].size();)
    if (b[u][i] == b[v][j])
    {
      intersect++;
      i++;
      j++;
    }
    else if (b[u][i] < b[v][j]) i++;
    else j++;
  return intersect >= n / 2;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  string s;
  cin >> n;
  for (int i = 1; i <= n + 1; i++)
  {
    cin >> s;
    id[i] = i;
    for (int p = 0; p < s.size(); p++)
      for (int q = 0; q < 6; q++)
      {
        int j = p * 6 + q;
        if (j < n * 2 && ((s[p] - 33) >> q & 1))
        {
          col[j]++;
          b[i].push_back(j);
        }
      }
    cout << endl;
  }

  random_shuffle(id + 1, id + n + 2);
  for (int i = 1; i <= n + 1; i++)
    if (isGood(id[i]))
      for (int j = 1; j <= n + 1; j++)
        if (i != j && isGood(id[i], id[j]))
        {
          cout << id[i] << ' ' << id[j] << endl;
          return 0;
        }
}