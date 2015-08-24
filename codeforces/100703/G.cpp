
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 1011;
int n, k, a[MN];
bitset<MN> f[MN], good;

void trace(int i, int j) {
    if (i == 0) return ;
    if (j >= a[i] && f[i-1].test(j-a[i])) {
        trace(i-1, j-a[i]);
        putchar('+');
    }
    else {
        trace(i-1, j+a[i]);
        putchar('-');
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        good.reset();
        FOR(i,0,k) good.set(i);
        FOR(i,1,n) f[i].reset();
        f[0].set(0);

        FOR(i,1,n) cin >> a[i];

        int savei = 0, savej = 0;
        FOR(i,1,n) {
            f[i] = (f[i-1] << a[i]) | (f[i-1] >> a[i]);
            f[i] &= good;
            FOR(j,0,k) if (f[i].test(j)) {
                savei = i;
                savej = j;
            }
        }
        printf("%d\n", savei);
        trace(savei, savej);
        puts("");
    }
}
