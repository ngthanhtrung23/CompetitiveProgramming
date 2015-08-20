#include <bits/stdc++.h>
using namespace std;

int n, a[1000100];
long long ans;

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

int main()
{
  freopen("huffman.in", "r", stdin);
  freopen("huffman.out", "w", stdout);
  priority_queue < pair<long long,int> > q;

  cin >> n;
  for (int i = 0; i < n; i++) 
  {
    GN(a[i]);
    q.push(make_pair(-a[i], i));
  }
  
  long long res = 0;
  while (q.size() > 1)
  {
    auto u = q.top(); 
    q.pop();
    auto v = q.top();
    q.pop();
    q.push(make_pair(u.first + v.first, n++));
    res -= u.first + v.first;
  }

  cout << res << endl;
}
