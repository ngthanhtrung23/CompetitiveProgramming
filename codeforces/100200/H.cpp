#include <bits/stdc++.h>
using namespace std;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

struct Point
{
  int x, y, z;
  Point() {}
  Point(int x, int y, int z): x(x), y(y), z(z) {}
};

int m, n, edge[444][444][4], dist[444][444][4];
Point tr[444][444][4];
string a[1010];

void trace(int x, int y, int z)
{
  if (x == m - 1 && y == 0) 
  {
    cout << (z ? "E" : "N") << endl;
    return;
  }
  Point p(tr[x][y][z]);
  trace(p.x, p.y, p.z);
  if (x || y != n - 1)
  {
    if (p.z == z) cout << "F";
    else if (p.z == (z + 1) % 4) cout << "L";
    else cout << "R";
  }
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("straight.in", "r", stdin);
  freopen("straight.out", "w", stdout);

  cin >> m >> n;
  getline(cin, a[0]);
  for (int i = 0; i < m * 2 - 1; i++)
    getline(cin, a[i]);

  for (int i = 0; i < m; i++)
    for (int j = 1; j < n * 2 && j < a[i * 2].size(); j += 2)
      if (a[i * 2][j] == '-')
        edge[i][j / 2][1] = edge[i][j / 2 + 1][3] = 1;

  for (int j = 0; j < n; j++)
    for (int i = 1; i < m * 2 && j * 2 < a[i].size(); i += 2)
      if (a[i][j * 2] == '|')
        edge[i / 2][j][2] = edge[i / 2 + 1][j][0] = 1;

  queue <Point> q;
  memset(dist, -1, sizeof dist);
  dist[m - 1][0][1] = dist[m - 1][0][0] = 0;
  q.push(Point(m - 1, 0, 0));
  q.push(Point(m - 1, 0, 1));

  while (!q.empty())
  {
    Point p = q.front();
    q.pop();
    if (p.x == 0 && p.y == n - 1)
    {
      trace(p.x, p.y, p.z);
      break;
    }

    if (!edge[p.x][p.y][p.z]) continue;
    int x = p.x + dx[p.z], y = p.y + dy[p.z];
    if (dist[x][y][p.z] < 0)
    {
      dist[x][y][p.z] = dist[p.x][p.y][p.z] + 1;
      tr[x][y][p.z] = p;
      q.push(Point(x, y, p.z));
    }

    for (int i = 1; i <= 3; i += 2)
    {
      int z = (p.z + i) % 4;
      if (dist[x][y][z] < 0)
      {
        dist[x][y][z] = dist[p.x][p.y][p.z] + 1;
        tr[x][y][z] = p;
        q.push(Point(x, y, z));
      }
    }
  }
}