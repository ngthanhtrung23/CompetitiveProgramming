
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

const int MN = 1000111;

ll res, save1, save2;
pair< pair<ll, ll>, ll > a[2][MN];
int n[2];


void solve(int turn) {
    vector< pair< int, pair<int,int> > > events;
    FOR(i,1,n[turn]) {
        events.push_back(make_pair(a[turn][i].first.first, make_pair(0, i)));
        events.push_back(make_pair(a[turn][i].first.second, make_pair(1, i)));
    }
    FOR(i,1,n[1-turn]) {
        events.push_back(make_pair(a[1-turn][i].first.first, make_pair(2, i)));
    }

    sort(events.begin(), events.end());

    set< pair<int,int> > all;

    for(auto e : events) {
        int typ = e.second.first;
        int id = e.second.second;

        if (typ == 0) { // add
            int b = a[turn][id].first.second;

            all.insert(make_pair(-b, id));
        }
        else if (typ == 1) { // add
            int b = a[turn][id].first.second;
            
            all.erase(make_pair(-b, id));
        }
        else {
            if (all.empty()) continue;

            long long x = a[1-turn][id].first.first;
            long long y = a[1-turn][id].first.second;
            long long c2 = a[1-turn][id].second;

            int id1 = all.begin()->second;
            long long A = a[turn][id1].first.first;
            long long B = a[turn][id1].first.second;
            long long c1 = a[turn][id1].second;

            long long cur = (min(B, y) - max(A, x)) * c1 * c2;
            if (cur > res) {
                res = cur;
                if (turn == 0) {
                    save1 = id1;
                    save2 = id;
                }
                else {
                    save1 = id;
                    save2 = id1;
                }
            }
        }
    }
}

int c[MN];
pair<int,int> bit[MN];

#define _(X) ((X) & (-(X)))
void update(int x, int val, int id) {
    while (x < MN) {
        bit[x] = max(bit[x], make_pair(val, id));
        x += _(x);
    }
}

pair<int,int> get(int x) {
    pair<int,int> res = make_pair(0, 0);
    while (x > 0) {
        res = max(res, bit[x]);
        x -= _(x);
    }
    return res;
}

void solve2() {
    // RR
    int sc = 0;
    FOR(i,1,n[0]) {
        c[++sc] = a[0][i].first.first;
        c[++sc] = a[0][i].first.second;
    }
    FOR(i,1,n[1]) {
        c[++sc] = a[1][i].first.first;
        c[++sc] = a[1][i].first.second;
    }
    sort(c+1, c+sc+1);
    sc = unique(c+1, c+sc+1) - c - 1;

    FOR(i,1,n[0]) {
        a[0][i].first.first = lower_bound(c+1, c+sc+1, a[0][i].first.first) - c;
        a[0][i].first.second = lower_bound(c+1, c+sc+1, a[0][i].first.second) - c;
    }
    FOR(i,1,n[1]) {
        a[1][i].first.first = lower_bound(c+1, c+sc+1, a[1][i].first.first) - c;
        a[1][i].first.second = lower_bound(c+1, c+sc+1, a[1][i].first.second) - c;
    }

//    cout << "First set: " << endl;
//    FOR(i,1,n[0]) {
//        cout << a[0][i].first.first << ' ' << a[0][i].first.second << endl;
//    }
//    cout << "Second set" << endl;
//    FOR(i,1,n[1]) {
//        cout << a[1][i].first.first << ' ' << a[1][i].first.second << endl;
//    }

    // Generate events
    vector< pair< int, pair<int,int> > > events;
    FOR(i,1,n[1]) {
        events.push_back(make_pair(a[1][i].first.first, make_pair(0, i)));
    }
    FOR(i,1,n[0]) {
        events.push_back(make_pair(a[0][i].first.first, make_pair(2, i)));
    }
    sort(events.begin(), events.end());

    memset(bit, 0, sizeof bit);
    for(auto e : events) {
        int typ = e.second.first;
        int id = e.second.second;

//        cout << typ << " " << id << endl;

        if (typ == 0) { // add
            int y = a[1][id].first.second;
            int c = a[1][id].second;

            update(sc - y + 1, c, id);
        }
        else {
            ll A = a[0][id].first.first;
            ll B = a[0][id].first.second;
            auto t = get(sc - B + 1);
            long long cc = t.first;
            int id2 = t.second;
            ll x = a[1][id2].first.first;
            ll y = a[1][id2].first.second;

            long long cur = cc * (min(c[B], c[y]) - max(c[A], c[x]));
            if (cur > res) {
                res = cur;
                save1 = id;
                save2 = id2;
            }
        }
    }
}


int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n[0], &n[1]) == 2) {
        FOR(i,1,n[0]) {
            int u, v; scanf("%d%d", &u, &v);
            a[0][i] = make_pair(make_pair(u, v), 1);
        }
        FOR(i,1,n[1]) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            a[1][i] = make_pair(make_pair(u, v), c);
        }
        res = 0;
        solve(0);

        FOR(i,1,n[0]) {
            a[0][i].first.first  = 1000000000 - a[0][i].first.first;
            a[0][i].first.second = 1000000000 - a[0][i].first.second;
            swap(a[0][i].first.first, a[0][i].first.second);
        }
        FOR(i,1,n[1]) {
            a[1][i].first.first  = 1000000000 - a[1][i].first.first;
            a[1][i].first.second = 1000000000 - a[1][i].first.second;
            swap(a[1][i].first.first, a[1][i].first.second);
        }
        solve(0);
        
        solve2();

        cout << res << endl;
        if (res) cout << save1 << ' ' << save2 << endl;
    }
    return 0;
}
