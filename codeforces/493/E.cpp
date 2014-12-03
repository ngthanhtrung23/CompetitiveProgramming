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
    long long t, a, b;
    while (cin >> t >> a >> b) {
        if (t == a && a != b) cout << 0 << endl;
        else if (t == a && a == b) {
            if (t == 1) cout << "inf" << endl;
            else cout << 2 << endl;
        }
        else if (a == b) cout << 1 << endl;
        else if (a > b) cout << 0 << endl;
        else if (t > a) cout << 0 << endl;
        else {
            int res = 0;
            if ((b - a) % (a - t) == 0) {
                vector<long long> repa, repb;
                if (t == 1) {
                    while (b % a == 0) {
                        repb.push_back(b % a);
                        b /= a;
                    }
                    long long sumb = 0;
                    for_each(repb.begin(), repb.end(), [&](int x) { sumb += x; });
                    if (b == 1 || a >= sumb) ++res;
                }
                else {
                    while (b) {
                        repb.push_back(b % a);
                        b /= a;
                    }
                    while (a) {
                        repa.push_back(a % t);
                        a /= t;
                    }
                    if (repa == repb) ++res;
                }
            }
            cout << res << endl;
        }
    }
    return 0;
}

