
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

int n;
set< vector<int> > all[55];

void get(int i, vector<int> x) {
    if (i == n) {
        all[i].insert(x);
        return ;
    }
    if (all[i].count(x)) return ;
    all[i].insert(x);

    // add new vector
    if (SZ(x) % 2 == i % 2) {
        vector<int> y = x;
        y.push_back(1);
        get(i+1, y);
    }

    vector<int> y = x;
    REP(row,SZ(x)) {
        if (row > 0 && x[row] + 1 > x[row-1]) continue;

        if ((row + x[row]) % 2 == i % 2) {
            y[row] ++;
            get(i+1, y);
            y[row] --;
        }
    }
}

int res[50] = {
    1,2,2,4,5,10,10,18,20,36,36,62,65,110,110,180,185,300,300,474,481,752,752,1154,1165,1770,1770,2650,2665,3956,3956,5800,5822,8470,8470,12200,12230,17490,17490,24800,24842,35002,35002,48954,49010,68150,68150,94158,94235,129512
};

int main() {
    ios :: sync_with_stdio(false);
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    while (cin >> n) cout << res[n-1] << endl;
//    FOR(n,1,50) {
//        ::n = n;
//        FOR(i,0,n) all[i].clear();
//        vector<int> x;
//        get(0, x);
//        cout << SZ(all[n]) << ',';
//        cout << flush;
//    }
//    cout << endl;
}
