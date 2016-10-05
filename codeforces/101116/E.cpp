#include <bits/stdc++.h>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) \
  { cout << #X << " = " << (X) << endl; }
#define PR(A, n)                      \
  {                                   \
    cout << #A << " = ";              \
    FOR(_, 1, n) cout << A[_] << ' '; \
    cout << endl;                     \
  }
#define PR0(A, n)                  \
  {                                \
    cout << #A << " = ";           \
    REP(_, n) cout << A[_] << ' '; \
    cout << endl;                  \
  }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

map<string, int> id;
string names[30111];

int getId(string s) {
  if (id.count(s)) return id[s];
  int res = SZ(id) + 1;
  id[s] = res;
  names[res] = s;
  return res;
}

int nGood, nBad, good[10111], bad[10111];
vector<int> ke[30111];
int visited[30111];

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  int ntest;
  cin >> ntest;
  while (ntest--) {
    id.clear();
    int m;
    cin >> nGood >> nBad >> m;
    FOR(i, 1, nGood) {
      string s;
      cin >> s;
      good[i] = getId(s);
    }
    FOR(i, 1, nBad) {
      string s;
      cin >> s;
      bad[i] = getId(s);
    }
    FOR(i, 1, m) {
      string a, b;
      cin >> a >> b;
      int u = getId(a);
      int v = getId(b);
      ke[u].push_back(v);
    }

    queue<int> qu;
    memset(visited, 0, sizeof visited);
    FOR(i, 1, nGood) {
      qu.push(good[i]);
      visited[good[i]] = true;
    }

    while (!qu.empty()) {
      int u = qu.front();
      qu.pop();

      for (int v : ke[u]) {
        if (!visited[v]) {
          visited[v] = 1;
          qu.push(v);
        }
      }
    }

    vector<string> res;
    FOR(i, 1, nBad) if (visited[bad[i]]) res.push_back(names[bad[i]]);
    sort(res.begin(), res.end());
    for (auto x : res) cout << x << ' ';
    cout << '\n';

    FOR(i, 0, SZ(id) + 1) ke[i].clear();
  }
}
