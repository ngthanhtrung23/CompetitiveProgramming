
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 100111;

int n, a[MN];
int minLeft[MN], maxLeft[MN], minRight[MN], maxRight[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);

        FOR(i,1,n) {
            if (i == 1) {
                minLeft[i] = maxLeft[i] = i;
            }
            else {
                minLeft[i] = minLeft[i-1]; if (a[i] < a[minLeft[i]]) minLeft[i] = i;
                maxLeft[i] = maxLeft[i-1]; if (a[i] > a[maxLeft[i]]) maxLeft[i] = i;
            }
        }
        FORD(i,n,1) {
            if (i == n) {
                minRight[i] = maxRight[i] = i;
            }
            else {
                minRight[i] = minRight[i+1]; if (a[i] < a[minRight[i]]) minRight[i] = i;
                maxRight[i] = maxRight[i+1]; if (a[i] > a[maxRight[i]]) maxRight[i] = i;
            }
        }
        bool has = false;
        FOR(i,2,n-1) {
            int u, v;

            u = minLeft[i-1], v = minRight[i+1];
            if (a[u] < a[i] && a[i] > a[v]) {
                cout << 3 << endl << u << ' ' << i << ' ' << v << endl;
                has = true;
                break;
            }

            u = maxLeft[i-1], v = maxRight[i+1];
            if (a[u] > a[i] && a[i] < a[v]) {
                cout << 3 << endl << u << ' ' << i << ' ' << v << endl;
                has = true;
                break;
            }
        }
        if (!has) cout << 0 << endl;
    }
}
