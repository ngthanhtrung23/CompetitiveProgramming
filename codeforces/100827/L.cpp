
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int n;
double x[66], y[66], z[66];
map<string,int> id;
string name[66];

double c[66][66];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cout << "Case " << test << ":\n";
        cin >> n;
        id.clear();
        FOR(i,1,n) {
            cin >> name[i]; id[name[i]] = i;
            cin >> x[i] >> y[i] >> z[i];
        }
        FOR(i,1,n) FOR(j,1,n) {
            c[i][j] = sqrt(sqr(x[i] - x[j])
                    + sqr(y[i] - y[j])
                    + sqr(z[i] - z[j]));
        }
        int m; cin >> m;
        while (m--) {
            string a, b; cin >> a >> b;
            int u = id[a];
            int v = id[b];
            c[u][v] = 0.0;
        }

        FOR(k,1,n)
            FOR(i,1,n) FOR(j,1,n)
                c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

        int q; cin >> q;
        while (q--) {
            string a, b; cin >> a >> b;
            int u = id[a], v = id[b];
            cout << "The distance from " << a << " to " << b << " is "
                << llround(c[u][v]) << " parsecs." << '\n';
        }
    }
}
