
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

const int MN = 2000111;

int n;
struct Exam {
    int t, c, day;
} a[MN];

vector<int> ev[2000 * 1011];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,2000*1000) ev[i].clear();

        FOR(i,1,n) {
            scanf("%d%d", &a[i].t, &a[i].c);
            ev[a[i].t].push_back(i);
        }
        set< pair<int,int> > all;
        FOR(time,1,1200111) {
            for(int id : ev[time]) {
                all.insert(make_pair(time - a[id].c, id));
            }

            if (!all.empty()) {
                auto p = *all.begin(); all.erase(all.begin());
                a[p.second].day = time;
            }
        }

        FOR(i,1,n) printf("%d ", a[i].day); puts("");
    }
    return 0;
}
