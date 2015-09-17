#include <bits/stdc++.h>
using namespace std;

int isGood(vector <string> s)
{
  set <string> blocks;
  for (int i = 0; i < s.size(); i++)
  {
    string block = s[i].substr(0, 1);
    for (int j = 1; j < s[i].size(); j++)
      if (s[i][j] != s[i][j - 1])
        block += s[i][j];
    if (block.size() > 2) return 0;
    if (block.size() == 1) continue;
    blocks.insert(block);
  }
  return blocks.size() < 2;
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("puzzle.in", "r", stdin);
  freopen("puzzle.out", "w", stdout);

  int it = 0, n;
  string a[55];
  while (cin >> n, n)
  {
    for (int i = 0; i < n; i++)
      cin >> a[i];

    if (it) cout << endl;
    int ans = 0;
    vector <string> s;
    for (int i = 0; i < n; i++)
      s.push_back(a[i]);
    ans |= isGood(s);

    s.clear();
    for (int j = 0; j < n; j++)
    {
      string row = "";
      for (int i = j; i < n; i++)
      {
        if (j < i) row += a[i][j * 2 + 1];
        row += a[i][j * 2];
      }
      s.push_back(row);
    }
    ans |= isGood(s);

    s.clear();
    for (int i = 0; i < n; i++)
      reverse(a[i].begin(), a[i].end());
    for (int j = 0; j < n; j++)
    {
      string row = "";
      for (int i = j; i < n; i++)
      {
        if (j < i) row += a[i][j * 2 + 1];
        row += a[i][j * 2];
      }
      s.push_back(row);
    }
    ans |= isGood(s);

    cout << "Puzzle " << ++it << endl;
    cout << "Parts can" << (ans ? "" : "not") << " be separated" << endl;
  }  
}