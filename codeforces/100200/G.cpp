#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-8;

int n, m, contestCnt[111];
double totalScore[111];
string teamName[111];

struct Contest
{
  int numTeam, numProb, numSub, teams[111];
  int maxSolved, solved[111][26], numSolved[111], totalPenalty[111], rank[111];

  void input()  
  {
    int x;
    cin >> numTeam;
    for (int i = 1; i <= numTeam; i++)
      cin >> teams[i];
    cin >> numProb >> numSub;
    memset(solved, 0, sizeof solved);
    memset(numSolved, 0, sizeof numSolved);
    memset(totalPenalty, 0, sizeof totalPenalty);
    maxSolved = 0;
    char ch, verdict;
    int t, penalty;
    for (int i = 0; i < numSub; i++)
    {
      cin >> t >> ch >> penalty >> verdict;
      int p = ch - 'A';
      if (solved[t][p] > 0) continue;
      if (verdict == '+')
      {
        solved[t][p] = penalty - solved[t][p] * 20;
        maxSolved = max(maxSolved, ++numSolved[t]);
        totalPenalty[t] += solved[t][p];
      }
      else solved[t][p]--;
    }
  }

  void process()
  {
    input();
    pair < pair<int,int>, int > teamOrder[111];
    for (int i = 1; i <= numTeam; i++)
    {
      int team = teams[i];
      teamOrder[i] = {{-numSolved[team], totalPenalty[team]}, team};
    }
    sort(teamOrder + 1, teamOrder + numTeam + 1);
    int currentRank = 1;
    for (int i = 1; i <= numTeam; i++)
      if (teamOrder[i].first == teamOrder[currentRank].first) rank[teamOrder[i].second] = currentRank;
      else rank[teamOrder[i].second] = currentRank = i;

    int A = 2 * numTeam - 2, B = numTeam - 2;
    for (int i = 1; i <= numTeam; i++)
    {
      double score = 0;
      int team = teamOrder[i].second;
      if (maxSolved) {
        score = -1.0 * teamOrder[i].first.first / maxSolved;
        score *= A;
        score /= (rank[team] + B);
      }
      contestCnt[team]++;
      totalScore[team] += score;
    }
  }
} contests[22];

int main()
{
  ios::sync_with_stdio(0);
  freopen("ranking.in", "r", stdin);
  freopen("ranking.out", "w", stdout);
  string s;

  cin >> n;
  getline(cin, s);
  for (int i = 1; i <= n; i++)
    getline(cin, teamName[i]);

  cin >> m;
  for (int i = 1; i <= m; i++)
    contests[i].process(); 

  vector < pair<double,string> > ans;
  for (int i = 1; i <= n; i++)
    if (contestCnt[i])
      ans.push_back(make_pair(-totalScore[i] / contestCnt[i], teamName[i]));
    else
      ans.push_back(make_pair(0.0, teamName[i]));

  sort(ans.begin(), ans.end());
  int max_len = 0;
  for(auto p : ans) max_len = max(max_len, (int) p.second.length());

  int num_len = 0;
  for (auto p : ans) {
    stringstream ss; ss << (fixed) << setprecision(4) << (-p.first + EPS);
    num_len = max(num_len, (int) ss.str().length());
  }

  cout << (fixed) << setprecision(4);

  for (auto p : ans) {
    cout << setw(max_len) << (left) << p.second << ' ';
    stringstream ss; ss << (fixed) << setprecision(4) << (-p.first + EPS);
    string s = ss.str();
    while (s.length() < num_len) s = " " + s;
    cout << s << endl;
  }
}