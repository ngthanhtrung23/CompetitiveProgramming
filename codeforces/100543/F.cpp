#include <bits/stdc++.h>
using namespace std;
const int BASE = int(1e9) + 9;

long long f[1000100][2][2], ways[30][30][30][3][3];
int length[3];
string s[3];

int get(int i, int j)
{
  if (j >= length[i]) return 0;
  return s[i][j] == '?' ? 27 : s[i][j] - 'a' + 1;
}

int cmp(int x, int y)
{
  if (x == y) return 0;
  return x < y ? 1 : 2;
}

void init()
{
  for (int c0 = 0; c0 <= 26; c0++)
    for (int c1 = 0; c1 <= 26; c1++)
      for (int c2 = 0; c2 <= 26; c2++)
      {
        int u = cmp(c0, c1), v = cmp(c1, c2);
        if (c0 && c1 && c2) ways[27][27][27][u][v]++;
        if (c0 && c1) ways[27][27][c2][u][v]++;
        if (c1 && c2) ways[c0][27][27][u][v]++;
        if (c0 && c2) ways[27][c1][27][u][v]++;
        if (c0) ways[27][c1][c2][u][v]++;
        if (c1) ways[c0][27][c2][u][v]++;
        if (c2) ways[c0][c1][27][u][v]++;
        ways[c0][c1][c2][u][v]++;
      }  
}

int main()
{
  init();
  
  ios::sync_with_stdio(0);
  //freopen("f.in", "r", stdin);
  
  int test;
  cin >> test;
  while (test--)
  {
    int n = 0;
    for (int i = 0; i < 3; i++) 
    {
      cin >> s[i];
      length[i] = s[i].size();
      n = max(n, length[i]);
    }
    
    f[0][0][0] = 1;
    for (int i = 0; i < n; i++)
    {
      memset(f[i + 1], 0, sizeof f[i + 1]);
      for (int u = 0; u < 2; u++)
        for (int v = 0; v < 2; v++)
        {
          int c[3];
          for (int j = 0; j < 3; j++) c[j] = get(j, i);
          for (int uu = 0; uu < 3; uu++)
            for (int vv = 0; vv < 3; vv++)
            {
              if (!u && uu == 2) continue;
              if (!v && vv == 2) continue;
              f[i + 1][u || uu][v || vv] += f[i][u][v] * ways[c[0]][c[1]][c[2]][uu][vv];
              f[i + 1][u || uu][v || vv] %= BASE;
            }
        }
    }
    
    cout << f[n][1][1] << endl;
  }
}