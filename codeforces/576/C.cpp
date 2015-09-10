
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

int n;
struct Hieu {
    int x, y;
    int id;

    void read() { scanf("%d%d", &x, &y); }
} a[1000111];

const int C = 1011;

bool operator < (const Hieu& a, const Hieu& b) {
    if (a.x / C != b.x / C) return a.x / C < b.x / C;
    else return a.y < b.y;
}

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            a[i].read();
            a[i].id = i;
        }

        sort(a+1, a+n+1);
        FOR(i,1,n) printf("%d ", a[i].id); puts("");
    }
}
