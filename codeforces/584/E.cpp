
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

const int MN = 2011;
int a[MN], b[MN], posa[MN], posb[MN], n;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) { cin >> a[i]; posa[a[i]] = i; }
        FOR(i,1,n) { cin >> b[i]; posb[b[i]] = i; }

//        PR(a, n);
//        PR(b, n);

        vector< pair<int,int> > res;
        FORD(i,n,1) {
            if (posb[a[i]] == i) continue; // it is good
            if (posb[a[i]] < i) continue;  // will be handled later

            int cur = i;
            FOR(j,cur+1,posb[a[cur]]) {
                if (posb[a[j]] <= cur) {
                    res.push_back(make_pair(cur, j));
                    swap(a[j], a[cur]);
//                    cout << "Swap: " << cur << ' ' << j << endl;
//                    PR(a, n);

                    cur = j;
                }
            }
        }

        int sum = 0;
        REP(i,SZ(res)) {
            pair<int,int> p = res[i];
            sum += abs(p.first - p.second);
        }
        cout << sum << endl;
        cout << SZ(res) << endl;
        REP(i,SZ(res)) {
            pair<int,int> p = res[i];
            cout << p.first << ' ' << p.second << '\n';
        }
    }
}

