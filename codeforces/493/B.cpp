#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n;
    while (cin >> n) {
        vector<int> a, b;
        int last = -1;
        FOR(i,1,n) {
            int u; cin >> u;
            if (u > 0) a.push_back(u), last = 1;
            else b.push_back(-u), last = 2;
        }
        long long sa = 0, sb = 0;
        for_each(a.begin(), a.end(), [&](int x) { sa += x; });
        for_each(b.begin(), b.end(), [&](int x) { sb += x; });
        if (sa > sb) cout << "first";
        else if (sa < sb) cout << "second";
        else if (a > b) cout << "first";
        else if (a < b) cout << "second";
        else if (last == 1) cout << "first";
        else cout << "second";
        cout << endl;
    }
    return 0;
}
