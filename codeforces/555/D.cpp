
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
using namespace std;

const int MN = 200111;

int n, q;
int a[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> q) {
        set< pair<int,int> > all;
        FOR(i,1,n) {
            cin >> a[i];
            all.insert(make_pair(a[i], i));
        }
        while (q--) {
            map< pair<int,int>, int > visited;
            int cur_len, cur_peg;
            cin >> cur_peg >> cur_len;
            int cur_dir = 0;
            int cur = a[cur_peg];

            visited[make_pair(cur, cur_dir)] = cur_len;

//            cout << "Query:" << endl;
//            cout << cur << ' ' << cur_len << ' ' << cur_peg << ' ' << cur_dir << endl;

            while (cur_len > 0) {
                if (cur_dir == 0) {
                    auto it = all.upper_bound(make_pair(cur + cur_len, n + 1));
                    --it;

                    int reduce = it->first - cur;
                    cur = it->first;
                    cur_len -= reduce;
                    cur_peg = it->second;
                    cur_dir = 1 - cur_dir;
                }
                else {
                    auto it = all.lower_bound(make_pair(cur - cur_len, 0));
                    
                    int reduce = cur - it->first;
                    cur = it->first;
                    cur_len -= reduce;
                    cur_peg = it->second;
                    cur_dir = 1 - cur_dir;
                }

                if (visited.count(make_pair(cur, cur_dir))) {
                    int reduce = visited[make_pair(cur, cur_dir)] - cur_len;
                    if (reduce == 0) break;

                    cur_len %= reduce;
                }
                visited[make_pair(cur, cur_dir)] = cur_len;
//                cout << cur << ' ' << cur_len << ' ' << cur_peg << ' ' << cur_dir << endl;
            }
            printf("%d\n", cur_peg);
        }
    }
}
