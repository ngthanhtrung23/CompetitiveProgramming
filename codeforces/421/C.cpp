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

#define next next_
const int MN = 100111;
int nPeople, nEvent, last[MN], next[MN];
pair<char,int> events[MN];
bool appear[MN];

bool check(int u) {
    map<int,int> enter;
    bool manualEnter = false;
    FOR(i,1,nEvent) if (events[i].second == u) {
        if (events[i].first == '-') enter[u] = 0, manualEnter = true;
        break;
    }
    FOR(i,1,nEvent) {
        if (events[i].first == '+') enter[events[i].second] = i;
        else {
            if (enter.count(events[i].second)) enter.erase(events[i].second);
            else if (events[i].second != u) {
                if (next[i] == 0 && !manualEnter) {
                    return false;
                }
            }
        }
        if (!enter.empty() && !enter.count(u)) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> nPeople >> nEvent) {
        memset(appear, false, sizeof appear);
        FOR(i,1,nEvent) {
            cin >> events[i].first >> events[i].second;
            appear[events[i].second] = true;
        }
        vector<int> res;
        FOR(i,1,nPeople) if (!appear[i]) res.push_back(i);

        memset(last, 0, sizeof last);
        memset(next, 0, sizeof next);
        FOR(i,1,nPeople) {
            next[i] = last[events[i].second];
            last[events[i].second] = i;
        }

        if (events[1].first == '+') {
            if (check(events[1].second))
                res.push_back(events[1].second);
        }

        int save = -1;
        FOR(i,1,nPeople) {
            if (next[i] == 0 && events[i].first == '-') {
                save = i;
            }
        }
        if (save > 0 && check(events[save].second)) {
            res.push_back(events[save].second);
        }

        sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        cout << res.size() << endl;
        for(int x : res) cout << x << ' '; cout << endl;
    }
    return 0;
}
