#include <bits/stdc++.h>
using namespace std;

int n, B, d[10100], sz[10100], idProvince[10100], numProvince, hq[10100];
vector <int> a[10100], provinces;

void visit(int x, int par)
{
  vector <int> curChild;
  for (auto y : a[x])
  {
    if (y == par) continue;
    visit(y, x);
    if (sz[y])
    {
      curChild.push_back(y);
      sz[x] += sz[y];
      if (sz[x] >= B)
      {
        sz[x] = 0;
        hq[++numProvince] = x;
        for (auto child : curChild)
          idProvince[child] = numProvince;
        curChild.clear();
      }
    }
  }

  for (auto child : curChild)
    d[child] = x;
  sz[x]++;
  if (sz[x] >= B)
  {
    sz[x] = 0;
    hq[++numProvince] = x;
    idProvince[x] = numProvince;
  }
  else if (!par)
    idProvince[x] = numProvince;
}

int get(int x)
{
  return x == d[x] ? x : d[x] = get(d[x]);
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("royal.in", "r", stdin);
  freopen("royal.out", "w", stdout);
  int x, y;

  cin >> n >> B;
  for (int i = 1; i <= n; i++) 
    d[i] = i;
  for (int i = 1; i < n; i++)
  {
    cin >> x >> y;
    a[x].push_back(y);
    a[y].push_back(x);
  }

  visit(1, 0);    

  cout << numProvince << endl;
  for (int i = 1; i <= n; i++)
  {
    if (!idProvince[i])
      idProvince[i] = idProvince[get(i)];
    cout << idProvince[i] << ' ';
  }

  cout << endl;
  for (int i = 1; i <= numProvince; i++)
    cout << hq[i] << ' ';
}