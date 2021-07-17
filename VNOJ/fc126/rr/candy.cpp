#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
#define CONTAIN(S,x) (((S)>>(x)) & 1)
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int INF = 1000111000111LL;
const int MN = 100111;

void updMax(int& f, int val) {
    if (val > f) f = val;
}

int32_t main() {
    ios::sync_with_stdio(0);
    // read input
    int nSegments; cin >> nSegments;

    vector< pair<int,int> > segments(nSegments);
    for (auto& seg : segments) {
        cin >> seg.first >> seg.second;
        --seg.first;
    }

    // RR
    vector<int> events;
    for (auto& seg : segments) {
        events.push_back(seg.first);
        events.push_back(seg.second);
    }
    sort(events.begin(), events.end());
    events.resize(unique(events.begin(), events.end()) - events.begin());
    
    for (auto& seg : segments) {
        seg.first = lower_bound(events.begin(), events.end(), seg.first) - events.begin();
        seg.second = lower_bound(events.begin(), events.end(), seg.second) - events.begin();
    }

    // which segments cover each point
    vector< vector<int> > covers(SZ(events));
    vector< vector<int> > add(SZ(events));
    REP(i,nSegments) {
        auto seg = segments[i];
        FOR(p,seg.first,seg.second-1) {
            covers[p].push_back(i);
        }
        add[seg.first].push_back(i);
    }

    // REP(i,SZ(events)) PR0(covers[i], SZ(covers[i]));

    // dp
    vector<int> cur(1<<8, -INF), next(1<<8, -INF);
    REP(mask,TWO(SZ(covers[0]))) {
        cur[mask] = (events[1] - events[0]) * __builtin_parity(mask);
    }
    // PR0(cur, TWO(SZ(covers[0])));

    vector<int> segIdToBit(nSegments + 1, -INF);
    for (int i = 1; i < SZ(events); i++) {
        std::fill(next.begin(), next.end(), -INF);

        REP(t,SZ(covers[i])) {
            segIdToBit[covers[i][t]] = t;
        }

        REP(mask,TWO(SZ(covers[i-1]))) {
            int newMask = 0;
            REP(j,SZ(covers[i-1])) {
                if (CONTAIN(mask,j)) {
                    int id = segIdToBit[covers[i-1][j]];
                    if (id < 0) continue;
                    newMask |= TWO(id);
                }
            }
            updMax(next[newMask], cur[mask]);
        }

        for (int x : add[i]) {
            int p = TWO(segIdToBit[x]);
            REP(mask,TWO(SZ(covers[i]))) {
                updMax(next[mask | p], next[mask]);
            }
        }

        if (i+1 < SZ(events)) {
            REP(mask,TWO(SZ(covers[i]))) {
                next[mask] += (events[i+1] - events[i]) * __builtin_parity(mask);
            }
        }

        // undo
        REP(t,SZ(covers[i])) {
            segIdToBit[covers[i][t]] = -1;
        }
        std::swap(cur, next);

        // PR0(cur, TWO(SZ(covers[i])));
    }
    cout << cur[0] << endl;

    return 0;
}
