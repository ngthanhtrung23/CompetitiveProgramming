
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

typedef set< pair<int,int> > Poly;

int m, n;
string a[55];
Poly orig;
map< pair<int,int>, Poly > all;

void print(const Poly& p) {
    int maxi = 0, maxj = 0, minj = 1e6, mini = 1e6;
    for(auto a : p) {
        maxi = max(maxi, a.first);
        mini = min(mini, a.first);

        maxj = max(maxj, a.second);
        minj = min(minj, a.second);
    }

    FOR(i,mini,maxi) {
        FOR(j,minj,maxj) {
            if (p.count(make_pair(i, j))) cout << '*';
            else cout << '.';
        }
        cout << endl;
    }
}

pair<int,int> getStart() {
    pair<int,int> res;
    FOR(i,1,m) FOR(j,1,n)
        if (a[i][j] == '*') {
            return make_pair(i, j);
        }
    return res;
}

Poly translate(int di, int dj) {
    Poly res;
    for(auto p : orig) {
        res.insert(make_pair(p.first + di, p.second + dj));
    }
    return res;
}

bool intersect(const Poly& p, const Poly& orig) {
    for(auto a : p)
        if (orig.count(a)) return true;
    return false;
}

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};
bool touch(const Poly& p, const Poly& orig) {
    for(auto a : p) {
        REP(dir,4) {
            int u = a.first + di[dir];
            int v = a.second + dj[dir];

            if (orig.count(make_pair(u, v))) return true;
        }
    }
    return false;
}

bool good(const Poly& p, const Poly& orig) {
    return !intersect(p, orig) && touch(p, orig);
}

Poly get_outer(const Poly& p) {
    Poly res;
    for(auto a : p) {
        REP(dir,4) {
            int u = a.first + di[dir];
            int v = a.second + dj[dir];

            if (!p.count(make_pair(u, v))) {
                res.insert(make_pair(u, v));
            }
        }
    }
    return res;
}

void add(Poly& all, const pair<int,int>& d) {
    for(auto a : orig) {
        int u, v;

        u = a.first + d.first;
        v = a.second + d.second;
        all.insert(make_pair(u, v));

        u = a.first - d.first;
        v = a.second - d.second;
        all.insert(make_pair(u, v));
    }
}

bool coverAll(const Poly& outer,
        pair<int,int> d1,
        pair<int,int> d2,
        pair<int,int> d3) {
    Poly all;

    add(all, d1);
    add(all, d2);
    add(all, d3);

    for(auto a : outer)
        if (!all.count(a)) return false;
    return true;
}

bool solve() {
    Poly outer = get_outer(orig);

//    print(orig);
//    print(outer);

    FOR(dx,0,50) FOR(dy,-50,50)
        if (dx > 0 || dy > 0) {
            auto cur = translate(dx, dy);
            if (good(cur, orig)) {
                all[make_pair(dx, dy)] = cur;

//                cout << "dx = " << dx << ", dy = " << dy << endl;
//                print(cur);
            }
        }

    for(auto it1 = all.begin(); it1 != all.end(); ++it1)
        for(auto it2 = it1; it2 != all.end(); ++it2) {
            Poly p1 = it1->second;
            Poly p2 = it2->second;

            if (!intersect(p1, p2)) {
                if (coverAll(outer, 
                            it1->first, 
                            it2->first,
                            make_pair(0, 0))) return true;
            }

            for(auto it3 = it2; it3 != all.end(); ++it3) {
                Poly p3 = it3->second;

                if (!intersect(p1, p3) && !intersect(p2, p3)) {
                    if (coverAll(outer,
                                it1->first,
                                it2->first,
                                it3->first)) return true;
                }
            }
        }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("tilings.in", "r", stdin);
    freopen("tilings.out", "w", stdout);

    while (cin >> a[m+1]) {
        ++m;
        n = max(n, SZ(a[m]));
    }

    FOR(i,1,m) a[i] = " " + a[i];

    auto start = getStart();
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '*') {
        orig.insert(make_pair(i - start.first, j - start.second));
    }
//    for(auto p : orig) cout << p.first << ' ' << p.second << endl;

    cout << (solve() ? "YES" : "NO") << endl;
}

