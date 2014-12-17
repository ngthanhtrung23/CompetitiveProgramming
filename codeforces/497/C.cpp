#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 400111;
struct Event {
    int typ, id, l;
} events[MN];

bool operator < (const Event &a, const Event &b) {
    if (a.l != b.l) return a.l < b.l;
    return a.typ < b.typ;
}

struct Actor {
    int c, d, k;
} actors[MN];

struct Part {
    int a, b, actor_id;
} parts[MN];

int nPart, nEvent, nActor;

void solve() {
    set< pair<int,int> > candidates;
    FOR(i,1,nEvent) {
        if (events[i].typ == 0) { // actor
            int actor_id = events[i].id;
            candidates.insert(make_pair(actors[actor_id].d, actor_id));

//            DEBUG(actor_id);
//            for(auto x : candidates) cout << x.second << ' '; cout << endl;
        }
        else { // part
            int part_id = events[i].id;
            auto it = candidates.lower_bound(make_pair(parts[part_id].b, 0));
//            DEBUG(part_id);
            if (it == candidates.end()) {
                cout << "NO" << endl;
                return ;
            }
            else {
                int actor_id = it->second;
                parts[part_id].actor_id = actor_id;
//                cout << "go to actor " << actor_id << endl;

                actors[actor_id].k--;
                if (actors[actor_id].k == 0) {
                    candidates.erase(make_pair(actors[actor_id].d, actor_id));
                }
            }
        }
    }
    cout << "YES" << endl;
    FOR(i,1,nPart)
        cout << parts[i].actor_id << ' ';
    cout << endl;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> nPart) {
        FOR(i,1,nPart) cin >> parts[i].a >> parts[i].b;
        cin >> nActor;
        FOR(i,1,nActor) cin >> actors[i].c >> actors[i].d >> actors[i].k;

        nEvent = 0;
        FOR(i,1,nPart) {
            ++nEvent;
            events[nEvent].typ = 1;
            events[nEvent].l = parts[i].a;
            events[nEvent].id = i;
        }
        FOR(i,1,nActor) {
            ++nEvent;
            events[nEvent].typ = 0;
            events[nEvent].l = actors[i].c;
            events[nEvent].id = i;
        }
        sort(events+1, events+nEvent+1);

        solve();

//        DEBUG("OK");
    }
    return 0;
}
