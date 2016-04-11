#include <bits/stdc++.h>
using namespace std;
const int CHAR = 2000100;

int n, v[1000100], l[1000100], st[1000100];
int node, tNext[CHAR][26], tSuffix[CHAR], pattern[CHAR];
long long f[1000100];
char s[1000100], t[111];

void addTrie(char t[])
{
  int len = strlen(t), x = 1;
  for (int i = 0; i < len; i++)
  {
    int ch = t[i] - 'a';
    if (!tNext[x][ch]) tNext[x][ch] = ++node;
    x = tNext[x][ch];
  }

  if (pattern[x] < 0 || pattern[x] > len)
    pattern[x] = len;
}

void build()
{
  queue <int> q;
  q.push(1);
  while (!q.empty())
  {
    int x = q.front();
    q.pop();
    for (int ch = 0; ch < 26; ch++)
    {
      int y = tNext[x][ch];
      if (!y) continue;
      int s = tSuffix[x];
      while (s && !tNext[s][ch]) s = tSuffix[s];
      tSuffix[y] = s ? tNext[s][ch] : 1;
      q.push(y);
    }
  }
}

int main()
{
  freopen("cenzura.in", "r", stdin);
  freopen("cenzura.out", "w", stdout);

  int m, test;
  scanf("%d", &test);
  while (test--)
  {
    scanf("%d%s", &n, s);
    memset(l, 0, sizeof l);
    memset(tNext, 0, sizeof tNext);
    memset(pattern, -1, sizeof pattern);
    memset(tSuffix, 0, sizeof tSuffix);
    node = 1;

    for (int i = 1; i <= n; i++)
      scanf("%d", v + i);

    scanf("%d", &m);
    while (m--)
    {
      scanf("%s", t);
      addTrie(t);
    }
    build();

    int x = 1;
    for (int i = 0; i < n; i++)
    {
      int ch = s[i] - 'a';
      while (x > 1 && !tNext[x][ch]) x = tSuffix[x];
      x = max(tNext[x][ch], 1);
      int y = x;
      while (y)
      {
        if (pattern[y] > 0)
          l[i + 1] = max(l[i + 1], i + 1 - pattern[y] + 1);  
        y = tSuffix[y];
      } 
    }

    int head = 1, tail = 1;
    st[1] = 0;
    for (int i = 1, bound = 0; i <= n; i++)
    {
      f[i] = f[st[head]] + v[i];
      bound = max(bound, l[i]);
      while (tail >= head && f[i] <= f[st[tail]])
        tail--;
      st[++tail] = i;
      while (st[head] < bound)
        head++;
    }

    cout << f[st[head]] << endl;
  }
}