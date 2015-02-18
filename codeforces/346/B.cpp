
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

string a, b, s;
#define next __next
int nexts[111][311];
int f[111][111][111];
int tr1[111][111][111], tr2[111][111][111], tr3[111][111][111];
char trc[111][111][111];

int nexta[111][311];
int nextb[111][311];

void trace(int l, int i, int j, int k) {
    if (l == 0) return ;

    trace(l-1, tr1[i][j][k], tr2[i][j][k], tr3[i][j][k]);
    cout << trc[i][j][k];
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> a >> b >> s) {
        int la = a.length(), lb = b.length(), ls = s.length();
        // nexts
        REP(i,ls) {
            FOR(c,'A','Z') {
                string cur = s.substr(0, i);
                cur += c;

                FORD(j,i+1,0) {
                    string need = s.substr(0, j);
                    if (cur.substr(cur.length() - need.length(), need.length()) == need) {
                        nexts[i][c] = j;
                        break;
                    }
                }
            }
        }

        map<char,int> last;
        // nexta
        FORD(i,la-1,0) {
            last[a[i]] = i;
            FOR(c,'A','Z') {
                if (last.count(c)) {
                    nexta[i][c] = last[c];
                }
                else nexta[i][c] = la;
            }
        }

        // nextb
        last.clear();
        FORD(i,lb-1,0) {
            last[b[i]] = i;
            FOR(c,'A','Z') {
                if (last.count(c)) {
                    nextb[i][c] = last[c];
                }
                else nextb[i][c] = lb;
            }
        }

        int res = 0;
        int save1 = 0, save2 = 0, save3 = 0;
        memset(f, -1, sizeof f);
        f[0][0][0] = 0;

        REP(i,la) REP(j,lb) REP(k,ls) if (f[i][j][k] >= 0)
            FOR(c,'A','Z') {
                int i2 = nexta[i][c], j2 = nextb[j][c], k2 = nexts[k][c];
                

                if (i2 >= la || j2 >= lb || k2 >= ls) {
                    continue;
                }

                ++i2; ++j2;

                if (f[i][j][k] + 1 > f[i2][j2][k2]) {
                    f[i2][j2][k2] = f[i][j][k] + 1;
                    tr1[i2][j2][k2] = i;
                    tr2[i2][j2][k2] = j;
                    tr3[i2][j2][k2] = k;
                    trc[i2][j2][k2] = c;

                    if (f[i2][j2][k2] > res) {
                        res = f[i2][j2][k2];
                        save1 = i2;
                        save2 = j2;
                        save3 = k2;
                    }
                }
            }
        if (res == 0) cout << 0 << endl;
        else {
            trace(res, save1, save2, save3);
            cout << endl;
        }
    }
    return 0;
}
