#include <bits/stdc++.h>
using namespace std;

struct Person
{
  string name;
  int age;
};

map <int,int> depId;
vector <Person> id[100100];
set < pair<int,int> > depSet[100100], officeSet;

string getDepartmentHead(int d)
{
  if (depSet[d].empty()) return "Vacant";
  return id[d][depSet[d].begin()->second].name;
}

string getOfficeHead()
{
  if (officeSet.empty()) return "Vacant";
  int d = officeSet.begin()->second;
  return getDepartmentHead(d);
}

int getId(int d)
{
  if (!depId.count(d))
    depId[d] = depId.size();
  return depId[d];
}

int getAge(string s)
{
  int res = 0;
  for (int i = 6; i < 10; i++)
    res = res * 10 + s[i] - '0';
  for (int i = 3; i < 5; i++)
    res = res * 10 + s[i] - '0';
  for (int i = 0; i < 2; i++)
    res = res * 10 + s[i] - '0';
  return res;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t, d, x, n;
  string name, s;

  cin >> n;
  while (n--)
  {
    cin >> t;
    if (t > 0)
    {
      cin >> d >> name >> s;
      d = getId(d);
      int age = getAge(s), k = id[d].size();
      id[d].push_back({name, age});
      if (!depSet[d].empty())
        officeSet.erase({depSet[d].begin()->first, d});
      depSet[d].insert({age, k});
      officeSet.insert({depSet[d].begin()->first, d});
    }
    else
    {
      int k;
      cin >> d >> k;
      k--;
      d = getId(d);
      officeSet.erase({depSet[d].begin()->first, d});
      depSet[d].erase({id[d][k].age, k});
      if (!depSet[d].empty())
        officeSet.insert({depSet[d].begin()->first, d});
    }

    cout << getOfficeHead() << ' ' << getDepartmentHead(d) << '\n';
  }
}