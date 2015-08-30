#include <bits/stdc++.h>
using namespace std;
const int oo = 27081993;

struct Movie 
{
  string title;
  int year, continent;

  Movie(string s)
  {
    for (int i = 1; i < int(s.size()); i++)
      if (s[i] == '"')
      {
        title = s.substr(0, i + 1);
        s.erase(0, i + 1);
        break;
      }

    stringstream ss;
    ss << s;
    ss >> year >> continent;
    year -= 1870;
    continent--;
  }
};

int n, f[135][5][6], g[135][5][5][6];
pair < pair<int,int>, int > tr[135][5][6];
vector <string> movies[135][5], movieAns;
vector < pair<int,int> > best[135];

void init()
{
  for (int year = 0; year < 135; year++)
  {
    for (int s = 0; s < 5; s++)
      for (int t = 0; t < 5; t++)
        for (int change = 0; change <= 5; change++)
          g[year][s][t][change] = -oo;

    int cnt = 0, total = 0;
    for (int s = 0; s < 5; s++)
    {
      if (movies[year][s].empty()) continue;
      g[year][s][s][0] = movies[year][s].size();
      cnt++;
      total += movies[year][s].size();
    }

    for (int s = 0; s < 5; s++)
      for (int t = 0; t < 5; t++)
        if (s != t)
        {
          vector <int> best;
          for (int u = 0; u < 5; u++)
            if (u != s && u != t)
              best.push_back(movies[year][u].size());
          sort(best.begin(), best.end(), greater<int>());

          int sum = movies[year][s].size() + movies[year][t].size();
          g[year][s][t][1] = sum;
          for (int i = 0; i < 3; i++)
          {
            sum += best[i];
            g[year][s][t][i + 2] = sum;
          }
        }
  }
}

vector <string> traceYear(int year, int s, int t, int change)
{
  vector <string> res;
  for (auto movie : movies[year][s])
      res.push_back(movie);

  vector < pair<int,int> > best;
  for (int u = 0; u < 5; u++)
    if (u != s && u != t)
      best.push_back(make_pair(movies[year][u].size(), u));

  sort(best.begin(), best.end(), greater < pair<int,int> >());

  for (int i = 0; i < change - 1; i++)
    for (auto movie : movies[year][best[i].second])
      res.push_back(movie);

  if (s != t)
  {
    for (auto movie : movies[year][t])
      res.push_back(movie);
  }

  reverse(res.begin(), res.end());
  return res;
}

void trace(int year, int cont, int change)
{
  auto curTr = tr[year][cont][change];
  if (curTr.second == -1) trace(year - 1, cont, change);
  else if (curTr.second == -2)
  {
    vector <string> movieThisYear = traceYear(year, curTr.first.first, cont, change);
    for (auto movie : movieThisYear)
      movieAns.push_back(movie);
    reverse(movieAns.begin(), movieAns.end());
    for (auto movie : movieAns)
      cout << movie << '\n';
  }
  else
  {
    vector <string> movieThisYear = traceYear(year, curTr.first.second, cont, curTr.second);
    for (auto movie : movieThisYear)
      movieAns.push_back(movie);
    trace(year - 1, curTr.first.first, change - curTr.second - (curTr.first.first != curTr.first.second));
  }
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("dvd.in", "r", stdin);
  freopen("dvd.out", "w", stdout);
  string s;
  cin >> n;
  getline(cin, s);
  for (int i = 0; i < n; i++)
  {
    getline(cin, s);
    Movie movie(s);
    movies[movie.year][movie.continent].push_back(movie.title);
  }

  init();
  for (int i = 0; i < 135; i++)
    for (int j = 0; j < 5; j++)
      for (int k = 0; k <= 5; k++)
        f[i][j][k] = -oo;

  int ans = 0;
  for (int i = 0; i < 135; i++)
  {
    if (i)
      for (int cont = 0; cont < 5; cont++)
        for (int change = 0; change <= 5; change++)
        {
          tr[i][cont][change] = {{0, 0}, -1};
          f[i][cont][change] = f[i - 1][cont][change];
        }

    for (int cont = 0; cont < 5; cont++)
      for (int change = 0; change <= 5; change++)
        for (int startCont = 0; startCont < 5; startCont++)
          for (int newCont = 0; newCont < 5; newCont++)
            for (int add = 0; add <= 5; add++)
            {
              int newChange = add + change + (startCont != cont);
              if (newChange > 5 || !i) continue;
              int value = f[i - 1][cont][change] + g[i][startCont][newCont][add];
              if (value > f[i][newCont][newChange])
              {
                f[i][newCont][newChange] = value;
                tr[i][newCont][newChange] = {{cont, startCont}, add};
              }
            }

    for (int cont = 0; cont < 5; cont++)
      for (int newCont = 0; newCont < 5; newCont++)
        for (int change = 0; change <= 5; change++)
          if (f[i][newCont][change] < g[i][cont][newCont][change])
          {
            f[i][newCont][change] = g[i][cont][newCont][change]; 
            tr[i][newCont][change] = {{cont, newCont}, -2};
          }

    for (int cont = 0; cont < 5; cont++)
      for (int change = 0; change <= 5; change++)
        ans = max(ans, f[i][cont][change]);
  }

  cout << ans << endl;
  for (int i = 0; i < 135; i++)
    for (int cont = 0; cont < 5; cont++)
      for (int change = 0; change <= 5; change++)
        if (f[i][cont][change] == ans)
        {
          trace(i, cont, change);
          return 0;
        }
}