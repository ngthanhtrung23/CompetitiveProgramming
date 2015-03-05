
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

int cnt[1011][1011];
queue< pair<int,int> > q;

void add(int x, int y, int n) {
    int old = cnt[x+500][y+500];
    cnt[x+500][y+500] += n;
    if (old < 4 && cnt[x+500][y+500] >= 4) {
        q.push(make_pair(x, y));
    }
}

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int main() {
    int n, nq;
    while (scanf("%d%d", &n, &nq) == 2) {
        memset(cnt, 0, sizeof cnt);
        add(0, 0, n);
        int turn = 0;
        while (!q.empty()) {
            ++turn;
            auto cur = q.front(); q.pop();
            int has = cnt[cur.first + 500][cur.second + 500];
            cnt[cur.first + 500][cur.second + 500] %= 4;

            REP(dir,4) {
                int x = cur.first + di[dir];
                int y = cur.second + dj[dir];
                add(x, y, has / 4);
            }
        }

        while (nq--) {
            int x, y; scanf("%d%d", &x, &y);
            if (x < -500 || y < -500 || x > 500 || y > 500) puts("0");
            else printf("%d\n", cnt[x+500][y+500]);
        }
    }
    return 0;
}
