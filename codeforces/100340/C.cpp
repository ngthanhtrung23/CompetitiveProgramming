#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }
using namespace std;

struct Request
{
  int client, chunk;
};

int n, k, has[222][222], numChunk[222], value[222][222], ans[222];
vector <int> client[222];
Request from[222];
vector <Request> to[222];
vector< pair<int,int> > cur;

void send(int x, int y, int chunk)
{
//  cout << x << " --> " << y << ' ' << chunk << endl;
  has[y][chunk] = 1;
  cur.push_back(make_pair(x, y));
  numChunk[y]++;
  client[chunk].push_back(y);
}

int comp(int x, int y, int z) // if y is better than z
{
  if (!z) return 1;
  if (value[x][y] != value[x][z])
    return value[x][y] > value[x][z];
  if (numChunk[y] != numChunk[z])
    return numChunk[y] < numChunk[z];
  return y < z;
}

int main()
{
  ios::sync_with_stdio(0); cin.tie(0);
  freopen("epig.in", "r", stdin);
  freopen("epig.out", "w", stdout);
  cin >> n >> k;
  for (int i = 1; i <= k; i++)
  {
    has[1][i] = 1;
    numChunk[1]++;
    client[i].push_back(1);
  }

  int clientLeft = n - 1;
  for (int r = 1; clientLeft; r++)
  {
//    DEBUG(r);
    for (int i = 2; i <= n; i++)
      if (numChunk[i] < k)
      {
        Request req = {0, 0};
        for (int j = 1; j <= k; j++)
          if (!has[i][j] && (!req.chunk || client[j].size() < client[req.chunk].size()))
            req.chunk = j;

        for (int j = 1; j <= n; j++)
          if (has[j][req.chunk] && (!req.client || numChunk[j] < numChunk[req.client]))
            req.client = j;

//        cout << i << ": " << req.chunk << ' ' << req.client << endl;

        from[i] = req;
        to[req.client].push_back({i, req.chunk});
      }

    for (int i = 1; i <= n; i++)
      if (!to[i].empty())
      {
        Request select = {0, 0};
        for (auto req : to[i])
          if (comp(i, req.client, select.client))
            select = req;
        send(i, select.client, select.chunk);
        if (numChunk[select.client] == k)
        {
          ans[select.client] = r;
          clientLeft--;
        }


        to[i].clear();
      }
    for(auto p : cur) {
        value[p.second][p.first] ++;
    }
    cur.clear();
  }

  for (int i = 2; i <= n; i++)
    cout << ans[i] << ' ';
}
