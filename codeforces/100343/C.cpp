#include <bits/stdc++.h>
using namespace std;
const double oo = 1e15;

struct Edge
{
  int x, y, z;
};

int n, m, onPath[20200], path[20200], P;
Edge e[20200];
vector <int> a[1010];

double getCost(int i, double dif)
{
  if (onPath[i]) return max(1., e[i].z - dif);
  return e[i].z + dif;
}

double ok(double dif)
{
  double pathDist = 0;
  for (int i = 1; i <= P; i++)
    pathDist += getCost(path[i], dif);

  priority_queue < pair<double,int> > q;
  double dist[1010];
  int done[1010] = {0};
  for (int i = 1; i <= n; i++)
    dist[i] = oo;

  dist[1] = 0;
  q.push({0, 1});
  while (!q.empty())
  {
    int x = q.top().second;
    q.pop();
    if (done[x]) continue;
    done[x] = 1;

    for (int i : a[x])
    {
      int y = (x == e[i].x ? e[i].y : e[i].x);
      if (!done[y] && dist[y] > dist[x] + getCost(i, dif))
      {
        dist[y] = dist[x] + getCost(i, dif);
        q.push({-dist[y], y});
      }
    }
  }

  return fabs(dist[n] - pathDist) < 1e-8;
}

int main()
{
  freopen("lateagain.in", "r", stdin);
  freopen("lateagain.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  int p, x;
  cin >> n >> m;
  for (int i = 1; i <= m; i++)
  {
    cin >> e[i].x >> e[i].y >> e[i].z;
    a[e[i].x].push_back(i);
    a[e[i].y].push_back(i);
  }

  cin >> P;
  for (int i = 1; i <= P; i++)
  {
    cin >> path[i];
    onPath[path[i]] = 1;
  }

  double low = 0, high = 1e5;
  for (int turn = 0; turn < 100; turn++)
  {
    double mid = (low + high) / 2;
    if (ok(mid)) high = mid;
    else low = mid;
  }

  cout << fixed << setprecision(9) << low << endl;
  for (int i = 1; i <= m; i++)
    cout << getCost(i, low) << ' ';
}