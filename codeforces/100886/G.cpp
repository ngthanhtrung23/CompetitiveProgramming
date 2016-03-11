#include <bits/stdc++.h>
using namespace std;

long long maxProduct = -1;
string ans;

void update(string s)
{
  long long product = 1;
  while (s.back() == '0')
    s.pop_back();
  for (char c : s)
    product *= c - '0';
  if (product > maxProduct)
  {
    maxProduct = product;
    ans = s;
  }
}

void solve(string l, string r)
{
  int i = l.size() - 1;
  while (i >= 0 && l[i] == r[i])
    i--;

  if (i < 0)
  {
    update(l);
    return;
  }

  string m = r;
  for (int j = 0; j < i; j++)
    m[j] = '0';
  solve(m, r);

  assert(m[i] != '0');
  m[i]--;
  for (int j = 0; j < i; j++)
    m[j] = '9';
  update(m);
}

int main()
{
  string l, r;
  cin >> l >> r;
  reverse(l.begin(), l.end());
  reverse(r.begin(), r.end());
  while (l.size() < r.size()) 
    l += '0';
  solve(l, r);
  reverse(ans.begin(), ans.end());
  cout << ans << endl;
}