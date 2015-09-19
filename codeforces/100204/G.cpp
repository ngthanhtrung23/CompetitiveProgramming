#include <bits/stdc++.h>
using namespace std;
const double oo = 1e15;

int n, d[111], m, b[444], c[444], cost[444];
double capa[111][111], flow[111][111], canInc[111];
vector <int> edgeId;

int findAugment()
{
  queue <int> q;
  memset(d, 0, sizeof d);
  d[1] = 1;
  canInc[1] = oo;
  q.push(1);
  while (!q.empty())
  {
    int x = q.front();
    if (x == n) return 1;
    q.pop();
    for (int y = 1; y <= n; y++)
      if (!d[y])
      {
        if (flow[x][y] < capa[x][y])
        {
          canInc[y] = min(canInc[x], capa[x][y] - flow[x][y]);
          d[y] = x;
          q.push(y);
        }
        else if (flow[y][x] > 0)
        {
          canInc[y] = min(canInc[x], flow[y][x]);
          d[y] = -x;
          q.push(y);
        }
      }
  }

  return 0;
}

void incFlow()
{
  int y = n;
  double value = canInc[n];
  while (1)
  {
    int x = d[y];
    if (x > 0) flow[x][y] += value;
    else flow[y][-x] -= value;
    if (x == 1) return;
    y = abs(x);
  }
}

int ok(double threshold)
{
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      capa[i][j] = flow[i][j] = 0;

  edgeId.clear();
  double sum = 0;
  for (int i = 0; i < m; i++)
    if (cost[i] <= threshold)
    {
      edgeId.push_back(i);
      sum += cost[i] - threshold;
    }
    else capa[b[i]][c[i]] = capa[c[i]][b[i]] = cost[i] - threshold;

  while (findAugment()) 
    incFlow();

  double maxFlow = 0;
  for (int i = 1; i <= n; i++)
    maxFlow += flow[1][i];

  for (int i = 0; i < m; i++)
  {
    int x = b[i], y = c[i];
    if (d[x] && !d[y] || d[y] && !d[x])
      edgeId.push_back(i);
  }

  return maxFlow + sum <= 0;
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("network.in", "r", stdin);
  freopen("network.out", "w", stdout);

  cin >> n >> m;
  for (int i = 0; i < m; i++)
    cin >> b[i] >> c[i] >> cost[i];

  double low = *min_element(cost, cost + m);
  double high = *max_element(cost, cost + m);
  for (int turn = 0; turn < 100; turn++)
  {
    double mid = (low + high) / 2;
    if (ok(mid)) high = mid;
    else low = mid;
  }

  ok(low);
  sort(edgeId.begin(), edgeId.end());
  edgeId.resize(unique(edgeId.begin(), edgeId.end()) - edgeId.begin());
  cout << edgeId.size() << endl;
  for (auto i : edgeId)
    cout << i + 1 << ' ';
}