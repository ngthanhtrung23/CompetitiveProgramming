
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

int n, a[111], used[111];

void print(const vector<int>& a) {
    cout << a.size();
    for(int x : a) cout << ' ' << x;
    cout << endl;
}

int main() {
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        vector<int> neg, pos, zero;

        memset(used, 0, sizeof used);
        FOR(i,1,n) if (a[i] == 0) {
            zero.push_back(a[i]);
            used[i] = true;
        }

        FOR(i,1,n) if (a[i] < 0) {
            used[i] = true;
            neg.push_back(a[i]);
            break;
        }

        FOR(i,1,n) if (a[i] > 0) {
            used[i] = true;
            pos.push_back(a[i]);
        }

        if (pos.empty()) {
            FOR(i,1,n) if (!used[i] && a[i] < 0) {
                used[i] = true;
                pos.push_back(a[i]);
                if (pos.size() == 2) break;
            }
        }

        FOR(i,1,n) if (!used[i]) {
            zero.push_back(a[i]);
        }

        print(neg);
        print(pos);
        print(zero);
    }
    return 0;
}
