#include <bits/stdc++.h>
using namespace std;

struct Segment
{
  int from, to, firstTrue, t;
};

int n, v[100100], a[100100];
char type[100100];
vector <Segment> good[100100], bad[100100];

void write()
{
  cout << "consistent" << endl;
  for (int i = 0; i < n; i++)
    cout << (a[i] ? 't' : 'f');
  exit(0);
}

// return number of true statements
int assign(int from, int to)
{
  int i = from, t = a[from] > 0;
  while (i != to)
  {
    int ii = (i + 1) % n;
    a[ii] = a[i] ^ (type[i] == '-');
    t += a[ii];
    i = ii;
  }
  return t;
}

void process(int from, int to)
{
  for (a[from] = 0; a[from] <= 1; a[from]++)
  {
    int t = assign(from, to);
    if (a[to]) good[v[to]].push_back({from, to, a[from], t});
    else bad[v[to]].push_back({from, to, a[from], t});
  }
}

int modify(vector <Segment> &toAdd, vector <Segment> &toRemove)
{
  int res = 0;
  for (auto s : toAdd)
    res += s.t;
  for (auto s : toRemove)
    res -= s.t;
  return res;
}

void trace(int k)
{
  for (int i = 0; i <= 100000; i++)
    if (i != k)
      for (auto s : bad[i])
      {
        a[s.from] = s.firstTrue;
        assign(s.from, s.to);
      }
  
  for (auto s : good[k])
  {
    a[s.from] = s.firstTrue;
    assign(s.from, s.to);
  }
}

int main()
{
  freopen("truth.in", "r", stdin);
  freopen("truth.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  int id = -1;
  for (int i = 0; i < n; i++)
  {
    cin >> type[i];
    if (type[i] == '$')
    {
      if (id < 0)
        id = i;
      cin >> v[i];
    }
  }

  if (id < 0)
  {
    for (a[0] = 0; a[0] <= 1; a[0]++)
    {
      assign(0, n - 1);
      if (a[0] == a[n - 1] ^ (type[n - 1] == '-'))
        write();
    }
    cout << "inconsistent" << endl;
    return 0;
  }

  int from = (id + 1) % n;
  while (1)
  {
    int to = from;
    while (type[to] != '$')
      to = (to + 1) % n;
    process(from, to);
    if (to == id)
      break;
    from = (to + 1) % n;
  }

  int sumT = 0;
  for (int i = 0; i <= 100000; i++)
    for (auto s : bad[i])
      sumT += s.t;

  for (int i = 0; i <= 100000; i++)
  {
    sumT += modify(good[i], bad[i]);
    if (sumT == i)
    {
      trace(i);
      write();
    }
    sumT += modify(bad[i], good[i]);
  }
  cout << "inconsistent" << endl;
}