#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;
const int LIM = 400;

int f[401][LIM + 1][LIM + 1], n;

int eval(int x, int y, int z)
{
  return (z * 1000 + x) * 1000 + y + 1;
}

pair <int,int> getXY(int x, int y, int z)
{
    int t[3];
    t[0] = x;
    t[1] = y + x;
    t[2] = z;
    sort(t, t+3);
    return make_pair(t[1] - t[0], t[2] - t[1]);
}

int main()
{
  pair <int,int> a[444];
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> a[i].first;
    a[i].second = i + 1;
  }

  sort(a, a + n);
  srand(2781993);
  random_shuffle(a, a + n);
  
  f[n][0][0] = 1;
  for (int i = n - 1; i >= 0; i--)
    for (int x = 0; x <= LIM; x++)
      for (int y = 0; y <= LIM; y++)
        if (f[i + 1][x][y])
        {
          // 0
          auto u = getXY(x, y, a[i].first);
          if (u.first <= LIM && u.second <= LIM)
            f[i][u.first][u.second] = eval(x, y, 0);
          // 1
          u = getXY(0, x + y, x + a[i].first);
          if (u.first <= LIM && u.second <= LIM)
            f[i][u.first][u.second] = eval(x, y, 1);
          // 2
          u = getXY(0, x, x + y + a[i].first);
          if (u.first <= LIM && u.second <= LIM)
            f[i][u.first][u.second] = eval(x, y, 2);
        }

  int best = LIM * 2 + 1, bestX, bestY;
  for (int x = 0; x <= LIM; x++)
    for (int y = 0; y <= LIM; y++)
      if (f[0][x][y])
      {
        int cur = x + y;
        if (cur < best) {
            best = cur;
            bestX = x;
            bestY = y;
        }
      }

  cout << best << endl;
  int x = bestX, y = bestY;
  vector <int> trace;
  for (int i = 0; i < n; i++)
  {
    int xx = f[i][x][y] / 1000 % 1000, yy = f[i][x][y] % 1000 - 1, zz = f[i][x][y] / 1000000;
    x = xx;
    y = yy;
    trace.push_back(zz);
  }

  vector < vector<int> > ans(3, vector<int>(1, 0));
  for (int i = n - 1; i >= 0; i--)
  {
    ans[trace[i]].push_back(a[i].second);
    ans[trace[i]][0] += a[i].first;
    sort(ans.begin(), ans.end());
  }

  for (auto v : ans)
  {
    cout << v.size() - 1 << ' ';
    for (int i = 1; i < v.size(); i++)
      cout << v[i] << ' ';
    cout << endl;
  }
}
