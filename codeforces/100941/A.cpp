#include <bits/stdc++.h>
using namespace std;

struct Orc
{
  string name;
  int point;
  vector <int> priorities;
};

int n, m, k, a[100100];
vector <Orc> orc;
vector <int> id, arm[100100];

bool cmp(int u, int v)
{
  return orc[u].point > orc[v].point;
}

bool cmpName(int u, int v)
{
  string s = orc[u].name, t = orc[v].name;
  int minLen = min(s.size(), t.size());
  for (int i = 0; i < minLen; i++)
    if (tolower(s[i]) < tolower(t[i])) return 1;
    else if (tolower(s[i]) > tolower(t[i])) return 0;
    else if (s[i] < t[i]) return 1;
    else if (t[i] < s[i]) return 0;
  return s.size() < t.size();
}

int main()
{
  freopen("army.in", "r", stdin);
  freopen("army.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);

  string s;
  int point, num, x;
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++)
    cin >> a[i];
  getline(cin, s);
  for (int i = 0; i < n; i++)
  {
    id.push_back(i);
    getline(cin, s);
    for (int j = 0; j < s.size(); j++)
      if (s[j] >= '0' && s[j] <= '9')
      {
        string name = s.substr(0, j);
        while (name.size() > 1 && name.back() == ' ')
          name.pop_back();
        while (name.size() > 1 && name[0] == ' ')
          name.erase(name.begin());
        s = s.substr(j);
        stringstream ss;
        ss << s;
        ss >> point;
        ss >> num;
        vector <int> p;
        while (num--)
        {
          ss >> x;
          p.push_back(x);
        }
        orc.push_back({name, point, p});
        break;
      }
  }
  
  sort(id.begin(), id.end(), cmp);
  for (int i = 0; i < n; i++)
  {
    int u = id[i];
    for (auto v : orc[u].priorities)
      if (arm[v].size() < a[v])
      {
        arm[v].push_back(u);
        break;
      }
  }

  for (int i = 1; i <= m; i++)
  {
    sort(arm[i].begin(), arm[i].end(), cmpName);
    for (auto u : arm[i])
      cout << orc[u].name << '\n';
    cout << '\n';
  }
}