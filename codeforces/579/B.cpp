
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

struct Pair {
    int x, y;
    int s;
} a[1000111];

bool operator < (const Pair& a, const Pair& b) {
    return a.s > b.s;
}
bool used[1011];
int mat[1011];

int main() {
    ios :: sync_with_stdio(false);

    int n;
    while (cin >> n) {
        n *= 2;
        int k = 0;
        FOR(i,1,n) FOR(j,1,i-1) {
            ++k;
            a[k].x = i;
            a[k].y = j;
            cin >> a[k].s;
        }
        sort(a+1, a+k+1);
        memset(used, 0, sizeof used);
        FOR(i,1,k) {
            if (!used[a[i].x] && !used[a[i].y]) {
                mat[a[i].x] = a[i].y;
                mat[a[i].y] = a[i].x;

                used[a[i].x] = used[a[i].y] = true;
            }
        }
        FOR(i,1,n) cout << mat[i] << ' '; cout << endl;
    }
}
