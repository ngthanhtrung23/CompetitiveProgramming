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
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        if (n == 5) {
            cout << "3 5 1" << endl;
            cout << "4 5 2" << endl;
            cout << "2 4 1" << endl;
            cout << "1 2 1" << endl;
            cout << "1 3" << endl;
            cout << "2 3" << endl;
            continue;
        }
        int half = n / 2;
        vector< pair< pair<int,int>, int > > edges;
        FOR(i,1,half)
            edges.push_back(make_pair(make_pair(i, i+half), 1));
        FOR(i,half+1,n-1)
            edges.push_back(make_pair(make_pair(i, i+1), (i-half)*2-1));
        for(auto e : edges)
            cout << e.first.first << ' ' << e.first.second << ' ' << e.second << endl;
        FOR(i,1,half-1) cout << i << ' ' << i+1 << endl;
        cout << "1 3" << endl;
    }
    return 0;
}
