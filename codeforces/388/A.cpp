#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int a[111];
int nPile, piles[111];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);

        nPile = 0;
        FOR(i,1,n) {
            if (nPile == 0) {
                piles[++nPile] = 1;
            }
            else {
                if (piles[1] <= a[i]) ++piles[1];
                else piles[++nPile] = 1;
            }
            sort(piles+1, piles+nPile+1);
        }
        cout << nPile << endl;
    }
    return 0;
}