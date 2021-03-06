
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int main() {
    ios :: sync_with_stdio(false);
    int nVideo, nServer;
    while (cin >> nVideo >> nServer) {
        multiset<long long> processing;
        while (nVideo--) {
            long long s, m; cin >> s >> m;
            if (processing.size() < nServer) {
                cout << s + m << '\n';
                processing.insert(s + m);
            }
            else {
                long long can = *processing.begin();
                processing.erase(processing.begin());

                s = max(s, can);
                cout << s + m << '\n';
                processing.insert(s + m);
            }
        }
    }
    return 0;
}
