
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int cnt[333], cur[333];
int n;
string a[222];
int id[33][10111];
int x[10111];

const int MN = 2000111;
char tr[MN];
int deg[MN];
vector<int> ke[MN];
int res[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("agnatic.in", "r", stdin);
    freopen("agnatic.out", "w", stdout);
    while (cin >> n) {
        try {
            memset(cnt, 0, sizeof cnt);
            FOR(i,1,n) {
                cin >> a[i];
                memset(cur, 0, sizeof cur);
                for(char c : a[i]) cur[c] += 1;
                for(char c : a[i]) {
                    if (cnt[c] == 0) cnt[c] = cur[c];
                    else if (cnt[c] != cur[c]) throw 1;
                }
            }
            int nid = 0;
            FOR(c,'A','Z') if (cnt[c] > 0) {
                FOR(t,1,cnt[c]) {
                    id[c - 'A'][t] = ++nid;
//                    cout << (char) c << ' ' << nid << endl;
                    tr[nid] = c;
                }
            }
            FOR(i,1,nid) {
                deg[i] = 0;
                ke[i].clear();
            }
            FOR(i,1,n) {
                memset(cur, 0, sizeof cur);
                FOR(j,1,SZ(a[i])) {
                    char c = a[i][j-1];
                    ++cur[c];

                    x[j] = id[c - 'A'][cur[c]];
                }
//                PR(x, SZ(a[i]));

                FOR(j,1,SZ(a[i]) - 1) {
                    int u = x[j], v = x[j+1];
                    ke[u].push_back(v);
                    ++deg[v];
                }
            }

            queue<int> qu;
            int nRes = 0;
            FOR(i,1,nid) if (deg[i] == 0) {
                qu.push(i);
            }
            while (!qu.empty()) {
                int u = qu.front(); qu.pop();
                res[++nRes] = u;
                for(int v : ke[u]) {
                    --deg[v];
                    if (deg[v] == 0) qu.push(v);
                }
            }
            if (nRes < nid) throw 2;

            puts("YES");
            FOR(i,1,nRes) putchar((char) tr[res[i]]);
            puts("");
        } catch (int e) {
            puts("NO");
        }
    }
}
