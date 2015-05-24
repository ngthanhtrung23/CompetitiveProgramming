
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

string ans;
int n;
pair<string,char> a[111];
int wrong[111], cnt;

void attempt(int turn) {
    if (cnt > 1) return ;
    if (turn == 6) {
        bool ok = true;
        FOR(i,1,n) if (a[i].second == '-' && wrong[i] < 3) ok = false;
        if (ok) ++cnt;
        return ;
    }

    FOR(pos, turn*8, turn*8+7) {
        bool ok = true;
        FOR(i,1,n) if (a[i].first[pos] != ans[pos]) {
            ++wrong[i];
            if (a[i].second == '+' && wrong[i] >= 3) ok = false;
        }

        if (ok) {
            attempt(turn + 1);
        }

        FOR(i,1,n) if (a[i].first[pos] != ans[pos]) --wrong[i];
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> ans) {
        cin >> n;
        FOR(i,1,n) cin >> a[i].first >> a[i].second;

        cnt = 0;
        memset(wrong, 0, sizeof wrong);
        attempt(0);
        cout << (cnt == 1 ? "Yes" : "No") << endl;
    }
    return 0;
}

