#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, lg2[200200];
long long budget, sumH[100100], maxH[100100], h[100100];
long long maxL[100100][20], maxR[100100][20];

long long getMaxL(int from, int to)
{
  int l = lg2[to - from + 1];
  return max(maxL[from][l], maxL[to - (1 << l) + 1][l]);
}

long long getMaxR(int from, int to)
{
  int l = lg2[to - from + 1];
  return max(maxR[from][l], maxR[to - (1 << l) + 1][l]);
}

int checkLeft(int i, long long limit)
{
  int low = 1, high = i - 1, id = 0;
  while (low <= high)
  {
    int mid = (low + high) / 2;
    if (getMaxL(mid, i - 1) >= limit)
    {
      id = mid;
      low = mid + 1;
    }
    else high = mid - 1;
  }
  assert(id);
  return id;
}

int checkRight(int i, long long limit)
{
  int low = i + 1, high = n, id = n + 1;
  while (low <= high)
  {
    int mid = (low + high) / 2;
    if (getMaxR(i + 1, mid) >= limit)
    {
      id = mid;
      high = mid - 1;
    }
    else low = mid + 1;
  }
  assert(id <= n);
  return id;
}

int ok(int i, long long newH)
{
  int idL = checkLeft(i, newH - i) + 1;
  int idR = checkRight(i, newH - (n - i)) - 1; 
  long long need = newH - h[i];
  if (idL < i)
  {
    need -= sumH[i - 1] - sumH[idL - 1];
    int len = i - idL;
    need += (newH - 1 + newH - len) * len / 2;
  }
  if (idR > i)
  {
    need -= sumH[idR] - sumH[i];
    int len = idR - i;
    need += (newH - 1 + newH - len) * len / 2;
  }
  return need <= budget;
}

const int MN = 100111;
int maxLeft[MN], maxRight[MN], maxHeight[MN];

#undef int
int main()
#define int long long
{
  ios::sync_with_stdio(0);
  freopen("landscape.in", "r", stdin);
  freopen("landscape.out", "w", stdout);

  cin >> n >> budget;
  for (int i = 1; i <= n; i++)
  {
    cin >> h[i];
    sumH[i] = sumH[i - 1] + h[i];
    maxL[i][0] = h[i] - i;
    maxR[i][0] = h[i] - (n - i);
  }

  for (int i = 1; i <= n; ++i) {
      if (i == 1) maxLeft[i] = h[i];
      else maxLeft[i] = max(maxLeft[i-1] + 1, h[i]);
  }
  for (int i = n; i >= 1; --i) {
      if (i == n) maxRight[i] = h[i];
      else maxRight[i] = max(maxRight[i+1] + 1, h[i]);
  }

  for (int i = 1; i <= n; i++)
    maxH[i] = min(maxLeft[i], maxRight[i]);

  for (int i = 0, j = 1; i <= 16; i++)
    while (j < 1 << (i + 1))
      lg2[j++] = i;

  for (int j = 1; 1 << j <= n; j++)
    for (int i = 1; i + (1 << j) - 1 <= n; i++)
    {
      maxL[i][j] = max(maxL[i][j - 1], maxL[i + (1 << j - 1)][j - 1]);
      maxR[i][j] = max(maxR[i][j - 1], maxR[i + (1 << j - 1)][j - 1]);
    }

  long long ans = 0;
  for (int i = 1; i <= n; i++)
  {
    long long low = 1, high = maxH[i] - h[i], best = 0;
    while (low <= high)
    {
      long long mid = (low + high) / 2;
      if (ok(i, h[i] + mid))
      {
        best = mid;
        low = mid + 1;
      }
      else high = mid - 1;
    }

    ans = max(ans, h[i] + best);
  }

  cout << ans << endl;
}
