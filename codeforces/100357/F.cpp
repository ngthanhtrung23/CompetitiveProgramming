#include <bits/stdc++.h>
using namespace std;

string toStr(int x)
{
  string s = "";
  while (x)
  {
    s += char(x % 10 + '0');
    x /= 10;
  }
  reverse(s.begin(), s.end());
  return s;
}

string getTerm(int x, int y)
{
  string xTerm = "x" + toStr(x);
  string yTerm = "y" + toStr(y);
  if (!y) return xTerm + "|" + xTerm;
  if (!x) return yTerm + "|" + yTerm;
  return xTerm + "|" + yTerm;
}

int main()
{
  freopen("merge.in", "r", stdin);
  freopen("merge.out", "w", stdout);
  int m, n;
  string s[44];
  cin >> m >> n;
  for (int i = 1; i <= m + n; i++)
  {
    string s = "";
    for (int x = 0; x <= m; x++)
    {
      int y = i - x;
      if (y < 0 || y > n) continue;
      string term = getTerm(x, y);
      if (s == "") s += term;
      else s = "(" + s + ")&(" + term + ")";
    }
    cout << s << endl;
  }
}