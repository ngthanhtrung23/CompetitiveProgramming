#include <bits/stdc++.h>
using namespace std;

char buf[22];
string toStr(long long x)
{
  memset(buf, 0, sizeof buf);
  sprintf(buf, "%I64d", x);
  return string(buf);
}

string toSubnet(long long x, int prefix)
{
  string res = "";
  for (int i = 3; i >= 0; i--)
  {
    res += toStr(x >> (i << 3) & 255);
    res += i ? '.' : '/';
  }
  return res + toStr(prefix);
}

struct Trie
{
  int used, bit;
  Trie *next[2];

  Trie(int bit): bit(bit) 
  {
    used = 0;
    next[0] = next[1] = NULL;
  }

  void add(long long x, int prefix)
  {
    if (!prefix) 
    {
      used = 1;
      return;
    }

    long long v = x >> bit & 1;
    if (!next[v])
      next[v] = new Trie(bit - 1);
    next[v] -> add(x, prefix - 1);
  }

  void get(vector <string> &ans, long long x)
  {
    if (used) return;
    for (int i = 0; i < 2; i++)
      if (!next[i]) ans.push_back(toSubnet(x | i << bit, 32 - bit));
      else next[i] -> get(ans, x | i << bit);
  }
};

int main()
{
  ios::sync_with_stdio(0);
  int test;
  cin >> test;
  for (int iTest = 1; iTest <= test; iTest++)
  {
    vector <string> ans;
    int n;
    string s;
    Trie *trie = new Trie(31);

    cin >> n;

    for (int id = 0; id < n; id++)
    {
      cin >> s;
      long long x = 0, cur = 0;
      for (int i = 0; i < s.size(); i++)
        if (s[i] == '/' || s[i] == '.')
        {
          x = x << 8 | cur;
          cur = 0;
        }
        else cur = cur * 10 + s[i] - '0';

      trie -> add(x, cur);
    }

    if (n) trie -> get(ans, 0);
    else ans.push_back("0.0.0.0/0");

    cout << "Case #" << iTest << ":" << endl << ans.size() << endl;
    for (auto s : ans)
      cout << s << endl;
  }  
}