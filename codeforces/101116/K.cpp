
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

const int MN = 1011;

int n;
vector<int> ke[MN];
map<string, int> id;

bool isUpper(char c) { return c >= 'A' && c <= 'Z'; }

int getId(string s) {
  assert(isUpper(s[0]));
  if (id.count(s)) return id[s];

  int res = SZ(id) + 1;
  id[s] = res;
  return res;
}

int f[1011];

void dfs(int u) {
  vector<int> all;
  for (int v : ke[u]) {
    dfs(v);
    all.push_back(f[v]);
  }
  sort(all.begin(), all.end(), greater<int>());
  f[u] = 0;
  REP(i, SZ(all)) { f[u] = max(f[u], all[i] + i); }
  f[u] = max(f[u], SZ(ke[u]) + 1);
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  while (cin >> n) {
    id.clear();

    FOR(i, 1, n) {
      string s;
      cin >> s;
      int u = getId(s);

      int k;
      cin >> k;
      while (k--) {
        cin >> s;
        if (!isUpper(s[0])) continue;

        int v = getId(s);
        ke[u].push_back(v);
      }
    }

    dfs(1);
    printf("%lld\n", f[1]);

    FOR(i, 0, SZ(id)) ke[i].clear();
  }
}
