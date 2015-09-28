
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

vector<int> ls[11];
int a[MN], n, k;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,0,10) ls[i].clear();

        FOR(i,1,n) {
            cin >> a[i];
            if (a[i] == 100) continue;

            int t = 10 - a[i] % 10;
            ls[t].push_back(i);
        }

        REP(t,10) {
            for(auto x : ls[t]) {
                if (k < t) break;
                a[x] += t;
                k -= t;
            }
        }

        FOR(i,1,n) {
            while (a[i] < 100 && a[i] % 10 == 0 && k >= 10) {
                k -= 10;
                a[i] += 10;
            }
        }
        int sum = 0;
        FOR(i,1,n) sum += a[i] / 10;
        cout << sum << endl;
    }
}
