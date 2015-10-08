#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  freopen("brackets.in", "r", stdin);
  freopen("brackets.out", "w", stdout);

  string s;
  char match[256];
  int ans = 0, from, to, f[100100];
  vector <int> st;

  match[')'] = '(';
  match[']'] = '[';
  memset(f, -1, sizeof f);

  cin >> s;
  for (int i = 0; i < s.size(); i++)
    if (s[i] == '(' || s[i] == '[') st.push_back(i);
    else
    {
      if (!st.empty() && match[s[i]] == s[st.back()])
      {
        f[i] = st.back();
        f[st.back()] = i;
        st.pop_back();
      }
      else st.clear();
    }

  for (int i = 0; i < s.size(); i++)
    if (!i || f[i - 1] < 0)
    {
      int j = f[i];
      while (j + 1 < s.size() && f[j + 1] >= 0)
        j = f[j + 1];
      if (j - i + 1 > ans)
      {
        ans = j - i + 1;
        from = i;
        to = j;
      }
    }

  if (ans) cout << s.substr(from, to - from + 1) << endl;
  else cout << endl;
}