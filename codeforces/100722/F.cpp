#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  int n, id, x, test;
  cin >> test;
  while (test--) 
  {
    cin >> n >> id;
    vector < pair<int,int> > q;
    for (int i = 0; i < n; i++) 
    {
      cin >> x;
      q.push_back(make_pair(x, i == id));
    }
    
    int t = 0;
    while (!q.empty())
    {
      if (max_element(q.begin(), q.end()) -> first > q[0].first) 
        rotate(q.begin(), q.begin() + 1, q.end());
      else
      {
        t++;
        if (q[0].second) 
        {
          cout << t << endl;
          break;
        }
        q.erase(q.begin());
      }
    }
  }  
}