#include <stdio.h>

char s[12309];

int FF[2309][12][12];
int F[2309][12][12];

bool f(int rem, int just, int level, bool tracing=false){
    int i;
    bool r=false;
    if (rem==0) return true;
    if (!tracing && FF[rem][just][level]++) return F[rem][just][level];

    for (i=1; i<=10; i++)
    if (s[i]=='1' && i!=just && i>level)
    if (f(rem-1, i, i-level)) {
        r=true;
        if (tracing) {
            printf("%d ", i);
            f(rem-1, i, i-level, true);
        }
        break;
    }

    //printf("f(%d, %d, %d) = %d\n", rem, just, level, r);
    return F[rem][just][level] = r;
}

int n;
main(){
    scanf("%s%d", s+1, &n);
    if (f(n, 0, 0)) {
        printf("YES\n");
        f(n, 0, 0, true);
        printf("\n");
    }
    else printf("NO\n");
}