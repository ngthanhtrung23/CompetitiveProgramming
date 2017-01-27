
#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
#define double long double
int GI(int& x) { return scanf("%lld", &x); }
const int MN = 800111;

struct Tri {
    int x, h;

    int area() const {
        return h * h;
    }
};

bool operator < (const Tri& a, const Tri& b) {
    return a.x < b.x;
}

bool contains(Tri a, Tri b) {
    int l1 = a.x - a.h, r1 = a.x + a.h;
    int l2 = b.x - b.h, r2 = b.x + b.h;
    
    return l1 <= l2 && r2 <= r1;
}


int commonArea(Tri a, Tri b) {
    assert(!contains(a, b));
    assert(!contains(b, a));

    int l1 = a.x - a.h, r1 = a.x + a.h;
    int l2 = b.x - b.h, r2 = b.x + b.h;

    if (r1 < l2 || r2 < l1) return 0;

    int l = max(l1, l2);
    int r = min(r1, r2);

    Tri res;
    res.x = (l + r) / 2.0;
    res.h = l - res.x;

    return res.area();
}

set<Tri> all;
int n;
Tri a[MN];
int totalArea;

void removeTri(set<Tri>::iterator it) {
    assert(it != all.end());

    bool hasRight = false;
    bool hasLeft = false;
    Tri right, left;

    // right
    auto it2 = it;
    ++it2;
    if (it2 != all.end()) {
        totalArea += commonArea(*it, *it2);
        hasRight = true;
        right = *it2;
    }

    // left
    it2 = it;
    if (it2 != all.begin()) {
        --it2;
        totalArea += commonArea(*it, *it2);

        hasLeft = true;
        left = *it2;
    }

    if (hasLeft && hasRight) totalArea -= commonArea(left, right);

    totalArea -= it->area();
    all.erase(it);
}

void addTri(const Tri& a) {
    all.insert(a);
    auto it = all.find(a);
    assert(it != all.end());

    bool hasLeft = false, hasRight = false;
    Tri left, right;

    // right
    auto it2 = it;
    ++it2;
    if (it2 != all.end()) {
        totalArea -= commonArea(*it, *it2);

        hasRight = true;
        right = *it2;
    }

    // left
    it2 = it;
    if (it2 != all.begin()) {
        --it2;
        totalArea -= commonArea(*it, *it2);

        hasLeft = true;
        left = *it2;
    }

    if (hasLeft & hasRight) totalArea += commonArea(left, right);

    totalArea += it->area();
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(3);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n;
        cin >> a[1].x;
        int ax, bx, cx;
        cin >> ax >> bx >> cx;

        cin >> a[1].h;
        int ah, bh, ch;
        cin >> ah >> bh >> ch;

        FOR(i,2,n) {
            a[i].x = ((ax * a[i-1].x + bx) % cx) + 1;
            a[i].h = ((ah * a[i-1].h + bh) % ch) + 1;
        }
        // mul 2
        FOR(i,1,n) {
            a[i].h *= 2;
            a[i].x *= 2;
        }

        all.clear();
        
        /*
        FOR(i,1,n) {
            bool bad = false;
            for(auto t : all)
                if (contains(t, a[i])) {
                    bad = true;
                    break;
                }
            if (bad) continue;

            vector<Tri> remove;
            for(auto t : all) {
                if (contains(a[i], t)) {
                    remove.push_back(t);
                }
            }
            for(auto r : remove) all.erase(r);

            for(auto t1 : all)
                for(auto t2 : all)
                    if (t1 < t2 || t2 < t1) {
                        assert(!contains(t1, t2));
                        assert(!contains(t2, t1));
                    }

            all.insert(a[i]);

            totalArea = 0;
            bool first = true;
            Tri last;
            for(auto t : all) {
                if (first) first = false;
                else totalArea -= commonArea(last, t);

                totalArea += t.area();
                last = t;
            }

            assert(res < (1LL<<62) - totalArea);
            res += totalArea / (double) 4.0;

//            cerr << "Tri: "; for(auto t : all) cerr << t.x << ' ' << t.h << ' ' << t.area() << "    "; cerr << endl;
//            DEBUG(totalArea / 4.0);
        }
        */

        double res = 0;
        totalArea = 0;
        FOR(i,1,n) {
            bool bad = false;
            // remove Tri on right
            while (!all.empty()) {
                auto it = all.lower_bound(a[i]);
                if (it == all.end()) break;

                if (contains(a[i], *it)) {
                    removeTri(it);
                }
                else if (contains(*it, a[i])) {
                    bad = true;
                    break;
                }
                else break;
            }
            // remove Tri on left
            while (!all.empty()) {
                auto it = all.lower_bound(a[i]);
                if (it == all.begin()) break;
                --it;

                if (contains(a[i], *it)) {
                    removeTri(it);
                }
                else if (contains(*it, a[i])) {
                    bad = true;
                    break;
                }
                else break;
            }

            if (bad) { res += totalArea / (double) 4.0; continue; }

            addTri(a[i]);

            assert(res < (1LL<<62) - totalArea);
            res += totalArea / (double) 4.0;

//            cerr << "Tri: "; for(auto t : all) cerr << t.x << ' ' << t.h << ' ' << t.area() << "    "; cerr << endl;
//            DEBUG(totalArea / 4.0);
        }

        cout << "Case #" << test << ": " << res << '\n';
        DEBUG(test);
    }
}
