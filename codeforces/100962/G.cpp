#include <bits/stdc++.h>
using namespace std;


int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int k;
  cin >> k;
  int n = k * k;
  cout << n << '\n';

  vector <int> block[111];
  for (int i = 0; i < n; i++)
    block[i / k].push_back(i + 1);

  for (int color = 0; color < k; color++)
  {
    for (int i = 0; i < k; i++)
    {
      if (i)
        cout << block[i][0] << ' ' << block[i - 1][0] << '\n';
      for (int j = 1; j < k; j++)
        cout << block[i][0] << ' ' << block[i][j] << '\n';
    }

    for (int i = 0; i < k; i++)
      rotate(block[i].begin(), block[i].begin() + 1, block[i].end());
    int tmp = block[k - 1][0];
    for (int i = k - 1; i; i--)
      block[i][0] = block[i - 1][0];
    block[0][0] = tmp;
  }
}