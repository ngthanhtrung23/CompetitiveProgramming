
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

set< pair<int,int> > a;

set< pair<int,int> > :: iterator get(int x) {
    auto it = a.upper_bound(make_pair(x+1, 0));

    if (it == a.begin()) return a.end();
    --it;

    if (it->second >= x) return it;
    else return a.end();
}

void addSegment(int l, int r) {
    // we know that l does not belong to any segment
    int savel = l, saver = r;

    // if we can merge to previous segment
    auto it = get(l - 1);
    if (it != a.end()) {
        l = it->first;
        a.erase(it);
    }

    // if we can merge to next segments
    while (true) {
        it = a.lower_bound(make_pair(l, l));
        if (it == a.end()) break;

        if (r >= it->first - 1) {
            saver = min(saver, it->first - 1);
            r = it->second;
            a.erase(it);
        }
        else break;
    }

    a.insert(make_pair(l, r));
    printf("%lld %lld\n", savel, saver);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (scanf("%lld", &n) == 1) {
        a.clear();
        while (n--) {
            int x; scanf("%lld", &x);
            if (x > 0) {
                int p; scanf("%lld", &p);

                // add a segment
                auto it = get(x);

                if (it == a.end()) {
                    addSegment(x, x+p-1);
                }
                else {
                    int from = it->second;
                    addSegment(it->second + 1, it->second + p);
                }
            }
            else {
                // remove a point
                x = -x;
                
                // find segment that contains x
                auto it = get(x);
                if (it != a.end()) {
                    int l = it->first, r = it->second;
                    a.erase(it);

                    if (l <= x - 1) a.insert(make_pair(l, x - 1));
                    if (x + 1 <= r) a.insert(make_pair(x + 1, r));
                }
            }

//            cout << "Current: "; for(auto p : a) cout << p.first << ' ' << p.second << "   "; cout << endl;
        }
    }
}
