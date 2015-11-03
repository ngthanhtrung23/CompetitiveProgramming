
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

const int MN = 10111;
int n;
string a[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        int sum = 0;
        FOR(i,1,n) {
            cin >> a[i];
            sum += SZ(a[i]);
        }
        char sep; cin >> sep;

        int each = sum / (n/2) + 1;
        multiset<string> left, right[11];
        FOR(i,1,n) {
            left.insert(a[i] + sep);
            right[SZ(a[i])].insert(a[i]);
        }
        FOR(i,1,n/2) {
            string x = *left.begin(); left.erase(left.begin());
            right[SZ(x) - 1].erase(right[SZ(x) - 1].find(x.substr(0, SZ(x) - 1)));
            int rem = each - SZ(x);

            string y = *right[rem].begin(); right[rem].erase(right[rem].begin());
            left.erase(left.find(y + sep));

            cout << x << y << '\n';
        }
        cout << '\n';
    }
}
