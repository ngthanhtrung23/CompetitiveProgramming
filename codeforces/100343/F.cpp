#include <bits/stdc++.h>
using namespace std;
const int BASE = 997;

int m, n, a[200200], b[200200], nextId[200200];
string s, t;
long long p[200200];

void gen(string s, int a[])
{
  int last[128] = {0};
  for (int i = 1; i <= s.size(); i++)
  {
    if (last[s[i - 1]]) 
      a[i] = i - last[s[i - 1]];
    last[s[i - 1]] = i;
  }
}

int main()
{
  freopen("substring.in", "r", stdin);
  freopen("substring.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> s >> t;
  m = s.size();
  n = t.size();
  gen(s, a);
  gen(t, b);

  for (int i = 1; i <= m; i++)
    if (a[i])
      nextId[i - a[i]] = i;

  for (int i = 0; i <= 200000; i++)
    p[i] = i ? p[i - 1] * BASE : 1;

  long long hashT = 0, hashS = 0;
  for (int i = 1; i <= n; i++)
  {
    hashS += p[i] * a[i];
    hashT += p[i] * b[i];
  }

  vector <int> ans;
  if (hashS == hashT)
    ans.push_back(1);

  for (int i = n + 1; i <= m; i++)
  {
    int j = i - n;
    hashS -= p[j] * a[j];
    if (nextId[j])
    {
      if (nextId[j] < i)
        hashS -= p[nextId[j]] * a[nextId[j]];
      a[nextId[j]] = 0;
    }
    hashS += p[i] * a[i];
    if (hashS == hashT * p[j])
      ans.push_back(i - n + 1);
  }

  cout << ans.size() << endl;
  for (int x : ans)
    cout << x << ' ';
}