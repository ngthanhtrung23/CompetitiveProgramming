#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 111;

int nx, ny, nz;
char a[MN][MN][MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> nx >> ny >> nz) {
        FOR(x,1,nx) FOR(y,1,ny) FOR(z,1,nz) cin >> a[x][y][z];
        int res = 0;
        FOR(x,1,nx) FOR(y,1,ny) FOR(z,1,nz) if (a[x][y][z] == '1') {
            vector< tuple<int,int,int> > u, v;

            if (a[x-1][y][z] == '1') u.push_back(make_tuple(x-1, y, z));
            if (a[x][y-1][z] == '1') u.push_back(make_tuple(x, y-1, z));
            if (a[x][y][z-1] == '1') u.push_back(make_tuple(x, y, z-1));

            if (a[x+1][y][z] == '1') v.push_back(make_tuple(x+1, y, z));
            if (a[x][y+1][z] == '1') v.push_back(make_tuple(x, y+1, z));
            if (a[x][y][z+1] == '1') v.push_back(make_tuple(x, y, z+1));

            bool found = false;
            for(auto p : u) for(auto q : v) {
                if (found) break;

                int cnt = 0;
                if (get<0>(p) < get<0>(q) && a[get<0>(p) + 1][get<1>(p)][get<2>(p)] == '1') ++cnt;
                if (get<1>(p) < get<1>(q) && a[get<0>(p)][get<1>(p) + 1][get<2>(p)] == '1') ++cnt;
                if (get<2>(p) < get<2>(q) && a[get<0>(p)][get<1>(p)][get<2>(p) + 1] == '1') ++cnt;

                if (cnt == 1) {
                    found = true;
                    break;
                }
            }
            if (found) ++res;
        }
        cout << res << endl;
    }
}
