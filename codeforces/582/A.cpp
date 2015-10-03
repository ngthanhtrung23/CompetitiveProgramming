
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

int x[511];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        multiset<int> s;
        FOR(i,1,n*n) {
            int a; cin >> a;
            s.insert(a);
        }

        FORD(i,n,1) {
            x[i] = *s.rbegin();

            s.erase(s.find(x[i]));

            FOR(j,i+1,n) REP(dir,2) {
                auto it = s.find(__gcd(x[i], x[j]));
                s.erase(it);
            }
        }

        FOR(i,1,n) cout << x[i] << ' '; cout << endl;
    }
}
