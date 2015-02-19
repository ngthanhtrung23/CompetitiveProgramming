
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

const int MN = 100111;

char tmp[MN];
int cnt[2][12], save[2][12];
deque<int> res[2], cur[2];

void add(int x, int y, bool front = true) {
    cnt[0][x]--;
    cnt[1][y]--;
    if (front) {
        cur[0].push_front(x);
        cur[1].push_front(y);
    } else {
        cur[0].push_back(x);
        cur[1].push_back(y);
    }
}

void reset() {
    REP(t,2) while (!cur[t].empty()) cur[t].pop_back();
    REP(c,10) cnt[0][c] = save[0][c], cnt[1][c] = save[1][c];
}

int main() {
    while (gets(tmp)) {
        int n = strlen(tmp);
        memset(cnt, 0, sizeof cnt);
        REP(t,2) while (!res[t].empty()) res[t].pop_back();

        REP(i,n) {
            int u = tmp[i] - '0';
            cnt[0][u]++;
            cnt[1][u]++;

            res[0].push_back(u);
            res[1].push_back(u);
        }

        REP(c,10) save[0][c] = cnt[0][c], save[1][c] = cnt[1][c];

        int best = -1;

        FOR(x,0,9) if (cnt[0][x] && cnt[1][10-x]) {
            reset();

            add(x, 10-x);
            if (!cur[0].empty()) {
                FOR(x,0,9) if (cnt[0][x]) {
                    int y = 9 - x;
                    while (cnt[0][x] && cnt[1][y]) add(x, y);
                }
            }
            while (cnt[0][0] && cnt[1][0]) add(0, 0, false);

            int can = cur[0].size();

            FOR(x,0,9) {
                while (cnt[0][x]) {
                    FOR(y,0,9) if (cnt[1][y]) {
                        add(x, y);
                        break;
                    }
                }
            }

            if (can > best) {
                res[0] = cur[0];
                res[1] = cur[1];
                best = can;
            }
            reset();
        }

        reset();
        while (cnt[0][0] && cnt[1][0]) add(0, 0, false);
        int can = cur[0].size();

        FOR(x,0,9) {
            while (cnt[0][x]) {
                FOR(y,0,9) if (cnt[1][y]) {
                    add(x, y);
                    break;
                }
            }
        }

        if (can > best) {
            res[0] = cur[0];
            res[1] = cur[1];
            best = can;
        }

        REP(t,2) {
            for(auto x : res[t]) printf("%d", x);
            puts("");
        }
    }
    return 0;
}
