/**

(x + t*vx)^2 + (y + t*vy)^2 + (z + t*vz)^2 = R^2

(x^2+y^2+z^2) - R^2
+ 2*(x*vx + y*vy + z*vz) * t
+ (vx^2 + vy^2 + vz^2) * t^2

 */
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

struct Event {
    long double time;
    int typ;  // +1, 0, -1

    int query_id;
};
bool operator < (const Event& a, const Event& b) {
    if (fabs(a.time - b.time) > 1e-6) {
        return a.time < b.time;
    }

    return a.typ > b.typ;
}

int res[100111];
vector<Event> events;

int32_t main() {
    ios::sync_with_stdio(0);
    int n, R;
    cin >> n >> R;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        int vx, vy, vz;
        cin >> x >> y >> z;
        cin >> vx >> vy >> vz;

        int c = x*x + y*y + z*z - R*R;
        int b = 2 * (x*vx + y*vy + z*vz);
        int a = vx*vx + vy*vy + vz*vz;

        int delta = b*b - 4*a*c;
        if (delta < 0) continue;  // vo nghiem

        long double x1 = (-b - sqrt((long double) delta)) / 2.0 / a;
        long double x2 = (-b + sqrt((long double) delta)) / 2.0 / a;

        if (x2 < 0) continue;

        if (x1 < 0) x1 = 0;

        events.push_back({x1, +1, 0});
        events.push_back({x2, -1, 0});
    }
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        events.push_back({(long double) t, 0, i});
    }

    sort(events.begin(), events.end());
    int cur = 0;
    for (auto event : events) {
        cur += event.typ;

        if (event.typ == 0) {
            res[event.query_id] = cur;
        }
    }

    for (int i = 0; i < q; i++) {
        cout << res[i] << '\n';
    }
    return 0;
}
