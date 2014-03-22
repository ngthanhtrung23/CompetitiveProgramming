#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 1000111;
const int MAX = 1000000;

int n;
int a[MN], b[MN];
bool taken[MN];

int main() {
    while (scanf("%d", &n) == 1) {
        memset(taken, false, sizeof taken);
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            taken[a[i]] = true;
        }

        int badPairs = 0, cur = 0;
        FOR(i,1,MAX/2) {
            if (taken[i] && taken[MAX+1-i]) {
                ++badPairs;
            }
            else if (taken[i]) {
                b[++cur] = MAX+1 - i;
            }
            else if (taken[MAX+1-i]) {
                b[++cur] = i;
            }
        }
        FOR(i,1,MAX/2) {
            if (!taken[i] && !taken[MAX+1-i] && badPairs) {
                b[++cur] = i;
                b[++cur] = MAX+1-i;
                --badPairs;
            }
        }

        printf("%d\n", n);
        FOR(i,1,n) printf("%d ", b[i]);
        puts("");
    }
    return 0;
}
