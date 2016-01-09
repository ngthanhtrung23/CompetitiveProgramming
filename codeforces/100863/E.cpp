#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int n;
pair<int,int> a[22];
int W, H;
bool used[22];

pair< pair<int,int>, pair<int,int> > res[22];
set< pair<int,int> > pos;

bool intersect(int u, int v, int x, int y) {
    if (y <= u) return false;
    if (v <= x) return false;
    return true;
}

bool intersect(pair<int,int> a, pair<int,int> b, pair<int,int> x, pair<int,int> y) {
    if (!intersect(a.first, b.first, x.first, y.first)) return false;
    if (!intersect(a.second, b.second, x.second, y.second)) return false;
    return true;
}

bool canPlace(int turn, pair<int,int> top, pair<int,int> bottom) {
    FOR(i,1,turn-1) {
        if (intersect(res[i].first, res[i].second, top, bottom)) {
            return false;
        }
    }
    return true;
}

bool contains(pair<int,int> top, pair<int,int> bottom, pair<int,int> p) {
    return (top.first <= p.first && p.first < bottom.first
            && top.second <= p.second && p.second < bottom.second);
}

void attempt(int turn, set< pair<int,int> >& pos) {
//    DEBUG(turn);
//    for(auto p : pos) cout << p.first << ' ' << p.second << "    "; cout << endl;
    if (turn > n) {
        FOR(i,1,n) {
            cout << res[i].first.first << ' ' << res[i].first.second << ' '
                << res[i].second.first << ' ' << res[i].second.second << endl;
        }
        throw 1;
    }
    FOR(i,1,n) if (!used[i]) {
        REP(rot,2) {
            auto top = *pos.begin();
            auto bottom = make_pair(top.first + a[i].first, top.second + a[i].second);
            if (bottom.first <= W && bottom.second <= H
                    && canPlace(turn, top, bottom)) {
                res[turn].first = top;
                res[turn].second = bottom;

//                cout << "Put: " << i << " --> "
//                    << res[turn].first.first << ' ' << res[turn].first.second << ' '
//                    << res[turn].second.first << ' ' << res[turn].second.second << endl;
                
                set< pair<int,int> > next;
                for(auto p : pos) {
                    if (p == top) continue;
                    if (contains(top, bottom, p)) continue;
                    next.insert(p);
                }
                REP(add,2) {
                    pair<int,int> p;
                    if (add == 0) {
                        if (bottom.first == W) continue;
                        p = make_pair(bottom.first, top.second);
                    }
                    else {
                        if (bottom.second == H) continue;
                        p = make_pair(top.first, bottom.second);
                    }

                    bool can = true;
                    FOR(i,1,turn-1) {
                        if (contains(res[i].first, res[i].second, p)) {
                            can = false;
                            break;
                        }
                    }
                    if (can) next.insert(p);
                }

                used[i] = true;
                attempt(turn+1, next);
                used[i] = false;
            }

            // rotate
            swap(a[i].first, a[i].second);
        }
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        if (n > 11) break;
        cin >> W >> H;
        FOR(i,1,n) cin >> a[i].first >> a[i].second;
        random_shuffle(a+1, a+n+1);

        memset(used, 0, sizeof used);
        try {
            pos.clear();
            pos.insert(make_pair(0, 0));
            attempt(1, pos);
        } catch (int e) {
            cout << endl;
        }
    }
}
