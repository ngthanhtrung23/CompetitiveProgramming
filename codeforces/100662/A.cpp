
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

vector<int> a;
string s;
int k; 

bool check(int val) {
    a.clear();
    REP(turn,val) a.push_back(0);
    FOR(i,0,k) REP(turn,s[i]-'0') a.push_back(i);

    REP(i,a.size()) if (a[i] > i) return false;
    return true;
}

int main() {
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> k >> s;
        int l = 0, r = 1000, res = 1000;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        cout << "Case #" << test << ": " << res << endl;
    }
    return 0;
}
