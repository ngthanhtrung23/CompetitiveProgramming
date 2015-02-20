
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

const int MN = 1000111;

int dist(int a, int b) {
    return abs(b - a);
}
int n, q;

struct Gap {
    int l, r;
    int f, pos;

    Gap(int l, int r) : l(l), r(r) {
        if (l == 1 && r == n) {
            f = 1000111000;
            pos = 1;
        }
        else if (l == 1) {
            f = dist(1, r+1);
            pos = 1;
        }
        else if (r == n) {
            f = dist(l-1, n);
            pos = n;
        }
        else {
            pos = (l + r) >> 1;
            f = min(dist(l-1, pos), dist(pos, r+1));
        }
    }
};

bool operator < (const Gap& a, const Gap& b) {
    if (a.f != b.f) return a.f > b.f;
    if (a.pos != b.pos) return a.pos < b.pos;
    return a.l < b.l;
}

int position_of[MN];
set<int> cars;
set<Gap> gaps;

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        cars.insert(0); cars.insert(n+1);
        Gap all(1, n);
        gaps.insert(all);

        while (q--) {
            int typ, id; scanf("%d%d", &typ, &id);
            if (typ == 1) {
                auto cur = *gaps.begin();
                gaps.erase(gaps.begin());

                position_of[id] = cur.pos;
                printf("%d\n", cur.pos);
//                cout << "Add car --> " << cur.pos << endl;
                cars.insert(cur.pos);

                auto it = cars.find(cur.pos);
                auto left = it; --left;
                auto right = it; ++right;

                int x = (*left) + 1;
                int y = (*right) - 1;

                if (x < cur.pos) gaps.insert(Gap(x, cur.pos - 1));
                if (cur.pos < y) gaps.insert(Gap(cur.pos + 1, y));
            }
            else {
                int pos = position_of[id];
//                cout << "Remove car: " << pos << endl;

                auto it = cars.find(pos);
                auto left = it; --left;
                auto right = it; ++right;

                int x = (*left) + 1;
                int y = (*right) - 1;

                gaps.erase(Gap(x, pos - 1));
                gaps.erase(Gap(pos + 1, y));

                cars.erase(pos);
                gaps.insert(Gap(x, y));
            }

//            cout << "Gaps: ";
//            for(auto gap : gaps) cout << gap.l << ' ' << gap.r << "     "; cout << endl;
        }
    }
    return 0;
}
