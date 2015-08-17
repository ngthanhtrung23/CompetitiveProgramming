
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
pair<ll,ll> islands[MN], gaps[MN];
ll bridges[MN];
int nIsland, nBridges;
int res[MN];

struct Event {
    int typ;
    ll x;
    int id;

    Event() {}
    Event(int typ, ll x, int id) : typ(typ), x(x), id(id) {}
} events[MN * 3];

bool operator < (const Event& a, const Event& b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.typ != b.typ) return a.typ < b.typ;
    return a.id < b.id;
}

int nEvent;

void solve() {
    memset(res, -1, sizeof res);
    set< pair<ll,int> > all;
    FOR(i,1,nEvent) {
        if (events[i].typ == 0) {
            // Add a gap
            int id = events[i].id;
            all.insert(make_pair(gaps[id].second, id));
        }
        else if (events[i].typ == 2) {
            int id = events[i].id;
            if (all.count(make_pair(gaps[id].second, id))) {
                puts("No");
                return ;
            }
        }
        else {
            int bridge_id = events[i].id;

            if (all.empty()) continue;

            auto it = all.begin();
            int gap_id = it->second;
            all.erase(it);

            assert(gaps[gap_id].first <= bridges[bridge_id]);
            assert(bridges[bridge_id] <= gaps[gap_id].second);

            res[gap_id] = bridge_id;
        }
    }
    puts("Yes");
    FOR(i,1,nIsland-1) printf("%d ", res[i]); puts("");
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> nIsland >> nBridges) {
        FOR(i,1,nIsland) cin >> islands[i].first >> islands[i].second;
        FOR(i,1,nBridges) cin >> bridges[i];

        nEvent = 0;
        FOR(i,1,nIsland-1) {
            gaps[i] = make_pair(islands[i+1].first - islands[i].second, islands[i+1].second - islands[i].first);
            events[++nEvent] = Event(0, gaps[i].first, i);
            events[++nEvent] = Event(2, gaps[i].second, i);

//            cout << "Gap: " << gaps[i].first << ' ' << gaps[i].second << endl;
        }
//        PR(bridges, nBridges);

        FOR(i,1,nBridges) {
            events[++nEvent] = Event(1, bridges[i], i);
        }
        sort(events+1, events+nEvent+1);

        solve();
    }
}

