#include <bits/stdc++.h>
using namespace std;
const int LEN = 5000005;

int n, m, k, a[200100], point[200200], slen;
vector <int> id, arm[200100], priorities[200100];
string name[200200];
char str[LEN];

int gn(int &id) {
  assert(id < slen);
  while (id < slen and !isdigit(str[id])) {
    id++;
  }
  int res = 0;
  while (id < slen and isdigit(str[id])) {
    res = res * 10 + str[id] - '0';
    id++;
  }
  return res;
}

bool cmp(int u, int v)
{
  return point[u] > point[v];
}

bool cmpName(int u, int v)
{
  string s = name[u], t = name[v];
  int minLen = min(s.size(), t.size());
  for (int i = 0; i < minLen; i++)
    if (tolower(s[i]) < tolower(t[i])) return 1;
    else if (tolower(s[i]) > tolower(t[i])) return 0;
    else if (s[i] < t[i]) return 1;
    else if (s[i] > t[i]) return 0;
  return s.size() < t.size();
}

int main()
{
  freopen("army.in", "r", stdin);
  freopen("army.out", "w", stdout);

  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= m; i++)
    scanf("%d", a + i);
  fgets(str,LEN,stdin);
  for (int i = 0; i < n; i++)
  {
    id.push_back(i);
    fgets(str,LEN,stdin);
    slen = strlen(str);
    int pos = 0;
    int lst = 0;
    while (pos < slen and !isdigit(str[pos])) {
      if (str[pos] != ' ') lst = pos;
      pos++;
    }
    point[i] = gn(pos);
    int num = gn(pos);
    for (int j = 0; j < num; j++)
      priorities[i].push_back(gn(pos));

    str[lst+1] = 0;
    name[i] = string(str);
  }
  
  sort(id.begin(), id.end(), cmp);
  for (int i = 0; i < n; i++)
  {
    int u = id[i];
    for (auto v : priorities[u])
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
      cout << name[u] << '\n';
    cout << '\n';
  }
}