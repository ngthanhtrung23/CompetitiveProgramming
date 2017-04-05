#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

char a[200111];
long long p10[200111];
long long l[200111], r[200111];
int m;

int main() {
  while (gets(a)) {
    scanf("%d\n", &m);

    p10[0] = 1;
    for(int i = 1; i < 200111; i++)
      p10[i] = p10[i-1] * 10 % m;

    int n = strlen(a);
    for(int i = 0; i < n; i++) {
      int x = a[i] - '0';

      if (i == 0) l[i] = x;
      else l[i] = (l[i-1] * 10 + x) % m;
    }

    r[n] = 0;
    for(int i = n-1, j = 0; i >= 0; i--, j++) {
      int x = a[i] - '0';
      r[i] = (r[i+1] + x * p10[j]) % m;
    }

    long long res = l[n-1];
    for(int i = 1; i < n; i++) if (a[i] != '0') {
      long long cur = (r[i] * p10[i] + l[i-1]) % m;
      if (cur < res) res = cur;
    }
    printf("%d\n", (int) res);
  }
}
