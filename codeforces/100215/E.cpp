#include <bits/stdc++.h>
using namespace std;

struct Matching {
    int n;
    vector< vector<int> > ke;
    vector< bool > seen;
    vector< int > matchL, matchR;

    Matching(int n) : n(n), ke(n), seen(n, false), matchL(n, -1), matchR(n, -1) {
    }

    void addEdge(int u, int v) {
        ke[u].push_back(v);
    }

    bool bpm(int u) {
        for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v) {
            if (seen[*v]) continue;
            seen[*v] = true;

            if (matchR[*v] < 0 || bpm(matchR[*v])) {
                matchL[u] = *v;
                matchR[*v] = u;
                return true;
            }
        }
        return false;
    }

    int match() {
        int res = 0;
        for(int i = 0; i < n; ++i) {
            for(int i = 0; i < n; ++i) seen[i] = false;
            if (bpm(i)) ++res;
        }
        return res;
    }
};

int n, onTable;
vector < pair<int,char> > a[2];
char trump;

int getRank(char c)
{
  if (c <= '9') return c - '6';
  if (c == 'T') return 4;
  if (c == 'J') return 5;
  if (c == 'Q') return 6;
  if (c == 'K') return 7;
  return 8;
}

int canCover(pair <int,int> u, pair <int,int> v)
{
  if (u.second == v.second) return u.first < v.first;
  return v.second == trump;
}

int ok(int mask)
{
  vector < pair<int,char> > b[2];
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < n; j++)
      if (mask >> a[i][j].first & 1)
        b[i].push_back(a[i][j]);
  Matching hk(max(b[0].size(), b[1].size()));
  for (int i = 0; i < b[0].size(); i++)
    for (int j = 0; j < b[1].size(); j++)
      if (canCover(b[0][i], b[1][j]))
        hk.addEdge(i, j);
  return hk.match() == b[0].size();
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("fool.in", "r", stdin);
  freopen("fool.out", "w", stdout);

  string s;
  cin >> n >> trump;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < n; j++)
    {
      cin >> s;
      if (s[2] == '*')
      {
        s = s.substr(0, 2);
        onTable |= 1 << getRank(s[0]);
      }
      a[i].push_back({getRank(s[0]), s[1]});
    } 

  for (int mask = 0; mask < 1 << 9; mask++)
    if (mask & onTable && ok(mask))
    {
      cout << "COVER" << endl;
      return 0;
    }

  cout << "TAKE" << endl;
}
