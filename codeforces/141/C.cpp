
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
struct Person {
    string name;
    int taller;
    int height;
} a[3011];
int x[3011];

bool operator < (const Person& a, const Person& b) {
    return a.taller < b.taller;
}

void solve() {
    int nx = 0;
    FOR(i,1,n) {
        if (a[i].taller > nx) {
            cout << -1 << endl;
            return;
        }

        int pos = nx+1;
        REP(turn,a[i].taller) {
            x[pos] = x[pos-1];
            --pos;
        }
        x[pos] = i;
        ++nx;
    }
    FOR(i,1,nx) a[x[i]].height = i;

    FOR(i,1,n) cout << a[i].name << ' ' << a[i].height << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i].name >> a[i].taller;
        sort(a+1, a+n+1);

        solve();
    }
}
