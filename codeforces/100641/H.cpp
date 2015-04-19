
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

double value[15][66][66];

void init() {
    REP(h,12) REP(m,60) REP(s,60) {
        int ss = m*60 + s;
        double big = (h % 12) * (360 / 12) + (ss / 3600.0) * 30;
        double small = (ss / 3600.0) * 360;
        
        if (small < big) small += 360;
        value[h][m][s] = small - big;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    init();
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int angle; string desc; int starth;
        cin >> angle >> desc >> starth;
        int saveh, savem, saves;

        int dir = (desc == "after" ? 1 : -1);
        for(int turn = 0, h = starth; turn < 12; ++turn, h = (h + dir + 12) % 12)
        REP(m,60) REP(s,60) {
            if (desc[0] == 't' && h%12 == starth%12) {
                if (m || s) continue;
            }
            if (h%12 == starth%12) {
                if (m == 0 && s == 0) continue;
            }
            double cur = value[h%12][m][s];

            int nexth = h, nextm = m, nexts = s + 1;
            if (nexts == 60) {
                ++nextm;
                nexts = 0;
                if (nextm == 60) {
                    ++nexth;
                    nextm = 0;
                }
            }

            double next = value[nexth%12][nextm][nexts];
            if (next < cur) next += 360;
            
            double val = angle;
            while (val < cur) val += 360;

            if (val <= next + 1e-6) {
                if (val - cur < next - val) {
                    saveh = h;
                    savem = m;
                    saves = s;
                    goto done;
                }
                else {
                    if (nexth%12 == starth%12 && nextm == 0 && nexts == 0) continue;
                    saveh = nexth;
                    savem = nextm;
                    saves = nexts;
                    goto done;
                }
            }
        }

done:
        saveh %= 12;
        if (saveh == 0) saveh = 12;
        printf("Case %d: %d:%02d:%02d\n", test, saveh, savem, saves);
    }
    return 0;
}
