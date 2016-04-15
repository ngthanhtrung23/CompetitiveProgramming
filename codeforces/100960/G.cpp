#include <bits/stdc++.h>
using namespace std;

int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}

int n, m, id[50500], V, cntV[200200];
long long a[100100], v[50500], realValues[200200], tree[200200];
map <long long,int> values;
multiset <long long> s;

void add(int x, long long v)
{
  for (int i = x; i <= V; i += i & -i)
    tree[i] += v;
}

long long get(int x)
{
  long long res = 0;
  for (int i = x; i; i -= i & -i)
    res += tree[i];
  return res;
}

int solve()
{
  int res = 0;
  long long sum = 0, last = 0;
  while (1)
  {
    auto it = s.lower_bound(max(sum, last + 1));
    if (it == s.end()) break;
    int id = values[*it];
    if (id > 1)
      sum = get(id - 1);

    if (realValues[id] >= sum)
    {
      last = realValues[id];
      res++;
    }

    if (cntV[id] > 1 && !sum)
      res *= 2;
    sum += realValues[id] * cntV[id];
  }
  return res;
}

int main()
{
  GN(n);
  for (int i = 1; i <= n; i++)
  {
    GN(a[i]);
    values[a[i]] = 0;
  }

  GN(m);
  for (int i = 1; i <= m; i++)
  {
    GN(id[i]);
    GN(v[i]);
    values[v[i]] = 0;
  }

  V = 0;
  for (auto u : values)
  {
    values[u.first] = ++V;
    realValues[V] = u.first;
  }

  for (int i = 1; i <= n; i++)
  {
    s.insert(a[i]);
    a[i] = values[a[i]];
    cntV[a[i]]++;
    add(a[i], realValues[a[i]]);
  }

  printf("%d\n", solve());
  for (int i = 1; i <= m; i++)
  {
    int x = id[i];
    cntV[a[x]]--;
    s.erase(s.find(realValues[a[x]]));
    add(a[x], -realValues[a[x]]);
    a[x] = values[v[i]];
    cntV[a[x]]++;
    s.insert(v[i]);
    add(a[x], v[i]); 
    printf("%d\n", solve());
  }
}