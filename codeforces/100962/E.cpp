#include <bits/stdc++.h>
using namespace std;

string conv(int n)
{
  if (!n) return "0";
  if (n == 1) return "1";
  string res = conv(n / 2);
  res += char(n % 2 + '0');
  return res;
}

int conv(string s)
{
  int res = 0;
  for (char c : s)
    res = res * 2 + c - '0';
  return res;
}

string get(string s, int i)
{
  string u = s.substr(0, i);
  if (s[i] == '0') u += '1';
  else u += '0';
  return u;
}

int main()
{
  int a, b;
  cin >> a >> b;
  if (a > b)
    swap(a, b);
  string s = conv(a), t = conv(b);

  if (s == t.substr(0, s.size()))
  {
    cout << -1 << endl;
    return 0;
  }

  set <int> ans;
  ans.insert(a);
  ans.insert(b);
  int diff = 0;
  for (int i = 1; i < t.size(); i++)
    if (!diff)
    {
      if (i >= s.size() || s[i] != t[i]) diff = 1;
      else ans.insert(conv(get(s, i)));
    }
    else
    {
      if (i < s.size())
        ans.insert(conv(get(s, i)));
      ans.insert(conv(get(t, i)));
    }

  for (int x : ans)
    cout << x << ' ';
}