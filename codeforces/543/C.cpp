
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

#define equal equal__
int maskSet[22][33], costSet[22][33], equal[22][22];
vector<int> allSet[22][33];
string s[22];

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int f[21][TWO(20)];
inline void update(int& x, int val) {
    if (x > val) x = val;
}

int a[22][22];
int main() {
    ios :: sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        FOR(i,1,n) {
            cin >> s[i];
            s[i] = " " + s[i];
        }
        FOR(i,1,n) FOR(j,1,m) cin >> a[i][j];

        FOR(i,1,n) FOR(j,1,m) {
            bool good = true;
            FOR(ii,1,n) if (ii != n && s[ii][j] == s[i][j]) good = false;

            if (good) equal[i][j] = true;
            else {
                equal[i][j] = a[i][j];
                int sum = 0;
                FOR(ii,1,n) if (ii != n && s[ii][j] == s[i][j]) sum += a[ii][j];
                equal[i][j] = min(equal[i][j], sum);
            }
        }

        FOR(i,1,n) FOR(j,1,m) FOR(c,0,26) {
            maskSet[j][c] = 0;
            costSet[j][c] = 0;
            allSet[j][c].clear();
        }

        FOR(i,1,n) FOR(j,1,m) {
            int c = s[i][j] - 'a';
            allSet[j][c].push_back(a[i][j]);
            maskSet[j][c] |= TWO(i-1);
        }
        FOR(j,1,m) FOR(c,0,26) if (maskSet[j][c]) {
            costSet[j][c] = 0;
            sort(allSet[j][c].begin(), allSet[j][c].end());

            // remove largest element
            allSet[j][c].pop_back();

            for(int x : allSet[j][c]) costSet[j][c] += x;
        }

        FOR(i,0,20) REP(mask,TWO(n)) f[i][mask] = 1000111000;
        f[0][0] = 0;
        FOR(i,1,m) {
            // previous row
            REP(mask,TWO(n)) f[i][mask] = f[i-1][mask];

            // update itself
            REP(mask,TWO(n)) {
                int t = f[i][mask];
                for(int c=0;c<26;++c) if (maskSet[i][c]) {
                    update(f[i][mask | maskSet[i][c]], t + costSet[i][c]);
                }
                for(int x=0;x<n;++x) if (!CONTAIN(mask,x))
                    update(f[i][mask | TWO(x)], t + equal[x+1][i]);
            }
        }
        cout << f[m][TWO(n)-1] << endl;
    }
    return 0;
}
