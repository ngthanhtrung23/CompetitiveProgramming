
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int n, a[100111];

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);

        if (n == 1) {
            if (a[1] == 0) {
                puts("YES");
                puts("0");
            }
            else {
                puts("NO");
            }
            continue;
        }
        if (a[n] == 1) {
            puts("NO");
            continue;
        }
        // now a[n] = 0
        if (a[n-1] == 1) {
            puts("YES");
            FOR(i,1,n-1) printf("%d->", a[i]);
            printf("%d\n", a[n]);
            continue;
        }
        int has = 0;
        FOR(i,1,n-2) if (a[i] == 0) has = i;

        if (!has) {
            puts("NO");
            continue;
        }
        puts("YES");
        --has;
        if (has) {
            putchar('(');
            FOR(i,1,has-1) printf("%d->", a[i]);
            printf("%d)->", a[has]);
        }
        putchar('(');
        printf("%d->(", a[has+1]);
        FOR(i,has+2,n-2) printf("%d->", a[i]);
        printf("%d))->", a[n-1]);
        printf("%d\n", a[n]);
    }
    return 0;
}

