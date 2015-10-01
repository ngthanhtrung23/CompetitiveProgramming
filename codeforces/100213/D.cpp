
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

const int MN = 50111;
int a[MN], n;
map<int,int> cnt;

int main() {
    ios :: sync_with_stdio(false);
    freopen("integer.in", "r", stdin);
    freopen("integer.out", "w", stdout);

    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        cnt.clear();
        
        int ln = -1, save = 0;
        FOR(i,1,n) {
            cnt[a[i] - i] += 1;
            if (cnt[a[i] - i] > ln) {
                ln = cnt[a[i] - i];
                save = a[i] - i;
            }
        }
        int cnt = 0;
        FOR(i,1,n) if (a[i] - i != save) ++cnt;
        cout << cnt << endl;
        FOR(i,1,n) cout << i + save << ' '; cout << endl;
    }
}
