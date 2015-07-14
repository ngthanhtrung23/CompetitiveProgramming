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

struct Query {
    int level;
    long long l, r;
    int ans;
} a[100111];

int h, q;
long long getMin(int level, long long x) {
    FOR(i,level+1,h) {
        x = x * 2;
    }
    return x;
}
long long getMax(int level, long long x) {
    FOR(i,level+1,h) {
        x = x * 2 + 1;
    }
    return x;
}

void solve() {
    long long from = getMin(1, 1);
    long long to = getMax(1, 1);

//    cout << from << " --> " << to << endl;
    FOR(i,1,q) if (a[i].ans == 1) {
        long long l = getMin(a[i].level, a[i].l);
        long long r = getMax(a[i].level, a[i].r);
        if (r < from || to < l) {
            cout << "Game cheated!" << endl;
            return ;
        }
        from = max(from, l);
        to = min(to, r);
    }
//    cout << from << " --> " << to << endl;

    set< pair<long long, long long> > all;
    all.insert(make_pair(from, to));

    FOR(i,1,q) if (a[i].ans == 0) {
        long long l = getMin(a[i].level, a[i].l);
        long long r = getMax(a[i].level, a[i].r);

        while (all.lower_bound(make_pair(l, 0)) != all.end()) {
            auto it = all.lower_bound(make_pair(l, 0));
            if (it->first <= r) {
                auto bad = *it;
                long long from = r+1, to = bad.second;
                if (from <= to) all.insert(make_pair(from, to));

                all.erase(bad);
            }
            else break;
        }
        auto it = all.lower_bound(make_pair(l, 0));
        if (it != all.begin()) {
            --it;
            if (it->second >= l) {
                auto bad = *it;
                long long from = bad.first, to = l - 1;
                if (from <= to) all.insert(make_pair(from, to));

                if (r < bad.second) {
                    from = r + 1, to = bad.second;
                    if (from <= to) all.insert(make_pair(from, to));
                }

                all.erase(bad);
            }
        }
    }
    long long sum = 0;
    for(auto p : all) sum += p.second - p.first + 1;
    if (sum == 0) {
        cout << "Game cheated!" << endl;
    }
    else if (sum > 1) {
        cout << "Data not sufficient!" << endl;
    }
    else cout << all.begin()->first << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> h >> q) {
        FOR(i,1,q) cin >> a[i].level >> a[i].l >> a[i].r >> a[i].ans;
        solve();
    }
}
