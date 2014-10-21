#include <bits/stdc++.h>
using namespace std;

int t;

int n;
int i,j;

int main() {
  scanf("%d",&t);
  while (t--) {
    scanf("%d",&n);
    for (i = -n; i<=n; i++) {
      for (j = -n; j <= n; j++) {
        if ((abs(i) + abs(j)) % 3 == 0)  
          printf("b");
        else
          printf("w");
      }
      printf("\n");
    }
  }
}