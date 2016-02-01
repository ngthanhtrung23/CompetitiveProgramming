
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

int INF = 1e9;
int B, I, D, C;
string s, t;
int ls, lt, f[3011][3011], tru[3011][3011];
char trc[3011][3011];
string res;
vector<pair<int,int> > rem;

void trace(int i, int j) {
    if (i == 0 && j == 0) return ;
    if (trc[i][j] == 'B') {
        trace(i, tru[i][j]);
        rem.push_back(make_pair(tru[i][j] + 1, j));
    }
    else if (trc[i][j] == 'I') {
        trace(i-1, j);
        res += 'I';
    }
    else if (trc[i][j] == 'D') {
        trace(i, j-1);
        res += 'D';
    }
    else {
        assert(trc[i][j] == 'C');
        trace(i-1, j-1);
        res += 'C';
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("block.in", "r", stdin);
    freopen("block.out", "w", stdout);
    while (cin >> B >> I >> D >> C) {
        cin >> s >> t;
        ls = SZ(s);
        lt = SZ(t);
        s = " " + s + " ";
        t = " " + t + " ";

        FOR(i,0,lt) {
            pair<int,int> nn = make_pair(INF, 0);
            FOR(j,0,ls) {
                // t[i], s[j]
                if (i == 0 && j == 0) f[i][j] = 0;
                else {
                    f[i][j] = INF;

                    // I
                    if (i > 0) {
                        int cur = f[i-1][j] + I;
                        if (cur < f[i][j]) {
                            f[i][j] = cur;
                            trc[i][j] = 'I';
                        }
                    }
                    // D
                    if (j > 0) {
                        int cur = f[i][j-1] + D;
                        if (cur < f[i][j]) {
                            f[i][j] = cur;
                            trc[i][j] = 'D';
                        }
                    }
                    // C
                    if (i > 0 && j > 0 && t[i] == s[j]) {
                        int cur = f[i-1][j-1] + C;
                        if (cur < f[i][j]) {
                            f[i][j] = cur;
                            trc[i][j] = 'C';
                        }
                    }
                    // B
                    if (j > 0) {
                        int cur = nn.first + B;
                        if (cur < f[i][j]) {
                            f[i][j] = nn.first + B;
                            trc[i][j] = 'B';
                            tru[i][j] = nn.second;
                        }
                    }
                }
                nn = min(nn, make_pair(f[i][j], j));
            }
        }
        res = "";
        rem.clear();
        cout << f[lt][ls] << endl;
        trace(lt, ls);
        cout << SZ(rem) << endl;
        for(auto p : rem) cout << p.first << ' ' << p.second << '\n';
        cout << res << endl;
    }
}
