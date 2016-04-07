#include <bits/stdc++.h>
using namespace std;

int n, k, canKill[111][22], f[1 << 20], tr[1 << 20], lv[2000100];
int xp[111], hp[111], damage[111], regen[111];
int creepHp[22], creepDamage[22], creepXp[22];

int getLevel(int curXp)
{
  return curXp >= xp[k] ? k : lv[curXp];
}

int die(int level, int i, int newLevel)
{
  int turn = (creepHp[i] + damage[level] - 1) / damage[level];
  int curHp = hp[level] - 1LL * turn * (creepDamage[i] - regen[level]);
  return curHp + hp[newLevel] - hp[level] <= 0;
}

int main()
{
  freopen("creeping.in", "r", stdin);
  freopen("creeping.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> k;
  for (int i = 1; i <= k; i++)
  {
    cin >> xp[i] >> hp[i] >> damage[i] >> regen[i];
    if (i > 1)
      for (int j = xp[i - 1]; j < xp[i]; j++)
        lv[j] = i - 1;
  }

  for (int i = 0; i < n; i++)
    cin >> creepHp[i] >> creepDamage[i] >> creepXp[i];

  for (int i = 1; i <= k; i++)
    for (int j = 0; j < n; j++)
    {
      int turn = (creepHp[j] + damage[i] - 1) / damage[i];
      if (hp[i] > 1LL * turn * (creepDamage[j] - regen[i]))
        canKill[i][j] = 1;
    }

  memset(f, -1, sizeof f);
  f[0] = 0;
  int ans = -1, bestMask;
  for (int mask = 0; mask < 1 << n; mask++)
    if (f[mask] >= 0)
    {
      if (f[mask] > ans)
      {
        ans = f[mask];
        bestMask = mask;
      }

      int level = getLevel(f[mask]);
      for (int i = 0; i < n; i++)
        if (!(mask >> i & 1) && canKill[level][i])
          if (f[mask | 1 << i] < 0)
          {
            int newLevel = getLevel(f[mask] + creepXp[i]);
            if (die(level, i, newLevel)) continue;
            f[mask | 1 << i] = f[mask] + creepXp[i];
            tr[mask | 1 << i] = i;
          }
    }

  cout << ans << endl;
  vector <int> creeps;
  while (bestMask)
  {
    creeps.push_back(tr[bestMask]);
    bestMask ^= 1 << tr[bestMask];
  }
  cout << creeps.size() << endl;
  reverse(creeps.begin(), creeps.end());
  for (auto u : creeps)
    cout << u + 1 << ' ';
}