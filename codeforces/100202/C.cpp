#include <bits/stdc++.h>
using namespace std;
const string MONTH[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const int oo = 27081993;

int yStart, yEnd, n, dLog[111], mLog[111], yLog[111], d[111], m[111], type[111];
int f[111][111], tr[111][111];

int readMonth(int &v)
{
  string s;
  cin >> s;
  for (int i = 0; i < 12; i++)
    if (MONTH[i] == s)
      v = i + 1;
}

int isLeapYear(int y)
{
  y += yStart;
  if (y % 400 == 0) return 1;
  if (y % 100 == 0) return 0;
  return y % 4 == 0;
}

int calc(int id, pair <int,int> startDate, int y, pair <int,int> endDate, int yy)
{
  set < pair<int,int> > holidays;
  for (int i = 1; i <= id; i++)
    if (type[i]) holidays.insert({m[i], d[i]});
    else holidays.erase({m[i], d[i]});

  int res = 0;
  for (auto date : holidays)
    if (date.first == 2 && date.second == 29)
    {
      if (y == yy) res += startDate < date && date <= endDate && isLeapYear(y);
      else
      {
        res += startDate < date && isLeapYear(y);
        res += date <= endDate && isLeapYear(yy);
        for (int i = y + 1; i < yy; i++)
          res += isLeapYear(i);
      }
    }
    else
    {
      if (y == yy) res += startDate < date && date <= endDate;
      else
      {
        res += startDate < date;
        res += date <= endDate;
        res += yy - y - 1;
      }
    }

  return res;
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("holidays.in", "r", stdin);
  freopen("holidays.out", "w", stdout);

  cin >> yStart >> yEnd >> n;
  yEnd -= yStart;
  for (int i = 1; i <= n; i++)
  {
    string s;
    readMonth(mLog[i]);
    cin >> dLog[i];
    cin >> s;
    cin >> s;
    type[i] = s == "added";
    readMonth(m[i]);
    cin >> d[i];
  }

  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= yEnd; j++)
      f[i][j] = -oo;

  for (int j = 0; j <= yEnd; j++)
    if (dLog[1] != 29 || mLog[1] != 2 || isLeapYear(j))
      f[1][j] = 0;

  for (int i = 2; i <= n + 1; i++)
    for (int j = 0; j <= yEnd; j++)
    {
      if (dLog[i] == 29 && mLog[i] == 2 && !isLeapYear(j)) continue;
      for (int jj = 0; jj <= j; jj++)
      {
        if (j == jj && make_pair(mLog[i - 1], dLog[i - 1]) >= make_pair(mLog[i], dLog[i]))
          continue;
        if (f[i - 1][jj] < 0) continue;
        int newF = f[i - 1][jj] + calc(i - 1, {mLog[i - 1], dLog[i - 1]}, jj, {mLog[i], dLog[i]}, j);
        if (newF > f[i][j])
        {
          f[i][j] = newF;
          tr[i][j] = jj;
        }
      }
    }

  int ans = -1, bestYear = -1;
  for (int j = 0; j <= yEnd; j++)
  {
    int v = f[n][j] + calc(n, {mLog[n], dLog[n]}, j, {12, 31}, yEnd);
    if (v > ans)
    {
      bestYear = j;
      ans = v;
    }
  }

  if (ans < 0)
  {
    cout << -1 << endl;
    return 0;
  }

  cout << ans << endl;
  for (int i = n; i; i--)
  {
    yLog[i] = bestYear;
    bestYear = tr[i][bestYear];
  }

  for (int i = 1; i <= n; i++)
  {
    cout << MONTH[mLog[i] - 1] << ' ' << dLog[i] << ' ' << yLog[i] + yStart << ", ";
    cout << (type[i] ? "added" : "removed");
    cout << ' ' << MONTH[m[i] - 1] << ' ' << d[i] << endl;
  }
}