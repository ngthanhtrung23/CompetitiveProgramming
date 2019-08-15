/**
 *    author:  tourist
 *    created: 30.07.2019 17:49:26       
**/
#include "bits/stdc++.h"
 
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

int main() {
  int n; GN(n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
      GN(a[i]);
  }
  int tt; GN(tt);
  vector<int> op(tt);
  vector<int> who(tt);
  vector<int> val(tt);
  for (int i = 0; i < tt; i++) {
      GN(op[i]);
    if (op[i] == 1) {
        GN(who[i]);
        GN(val[i]);
      --who[i];
    } else {
        GN(val[i]);
    }
  }
  vector<int> res(n, -1);
  int mx = -1;
  for (int i = tt - 1; i >= 0; i--) {
    if (op[i] == 1) {
      if (res[who[i]] == -1) {
        res[who[i]] = max(val[i], mx);
      }
    } else {
      mx = max(mx, val[i]);
    }
  }
  for (int i = 0; i < n; i++) {
    if (res[i] == -1) {
      res[i] = max(a[i], mx);
    }
  }
  for (int i = 0; i < n; i++) {
    if (i > 0) {
        putchar(' ');
    }
    printf("%d", res[i]);
  }
  putchar('\n');
  return 0;
}
