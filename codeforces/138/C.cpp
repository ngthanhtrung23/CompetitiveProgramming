
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

const int MN = 500111;

struct Event {
    int x;
    int typ;
    int prob;

    Event(int x = 0, int typ = 0, int prob = 0) : x(x), typ(typ), prob(prob) {}
} events[MN];

bool operator < (const Event &a, const Event& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.typ < b.typ;
}

int values[MN];

int main() {
    int nTree, nMush;
    while (scanf("%d%d", &nTree, &nMush) == 2) {
        int nEvent = 0;
        FOR(i,1,nTree) {
            int a, h, l, r;
            scanf("%d%d%d%d", &a, &h, &l, &r);

            events[++nEvent] = Event(a-h, 1, 100 - l);
            events[++nEvent] = Event(a-1, 3, 100 - l);

            events[++nEvent] = Event(a+1, 1, 100 - r);
            events[++nEvent] = Event(a+h, 3, 100 - r);
        }
        FOR(i,1,nMush) {
            int x;
            scanf("%d%d", &x, &values[i]);

            events[++nEvent] = Event(x, 2, i);
        }
        sort(events+1, events+nEvent+1);

        double log_prob = log(1.0);
        double res = 0.0;
        int u, zero = 0;
        FOR(i,1,nEvent) {
            switch (events[i].typ) {
                case 1:
                    u = events[i].prob;
                    if (u == 0) zero++;
                    else log_prob += log(events[i].prob / 100.0);
                    break;
                case 2:
                    u = events[i].prob;
                    if (!zero) res += exp(log_prob) * values[u];
                    break;
                case 3:
                    u = events[i].prob;
                    if (u == 0) --zero;
                    else log_prob -= log(events[i].prob / 100.0);
                    break;
            }
        }
        cout << (fixed) << setprecision(12) << res << endl;
    }
    return 0;
}

