/**
Problem:
- There are 2 rows of items (`front` and `back`).
- Each item has `price` and `height`.
- In each row, items must be sorted in increasing order of `price`.
- In each column, item in `front` row must have smaller height than item in
  `back` row.

Idea:
- Sort `front` and `back` rows in increasing order of price.
- Construct the 2 permutations from left to right.
- When we construct i-th element:
  - Let sFront = set of all heights in front row
  - Let sBack = set of all heights in back row
  - (We can create sFront and sBack by adding elements with equal price).
  - If |sFront| < |sBack|, we know all elements in sFront must be used
    --> for each of them, we greedily choose one element in sBack with min height.
  - |sBack| < |sFront|: solve similarly.
*/
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
// On CF, GNU C++ seems to have some precision issues with long double?
// #define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define stat akjcjalsjcjalscj
#define hash ajkscjlsjclajsc
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (((S) >> (X)) & 1)

long long rand16() {
    return rand() & (TWO(16) - 1);
}
long long my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(long long& x) { return scanf("%lld", &x); }

struct Tile {
    int price;
    int height;
    int id;
};

bool operator < (const Tile& a, const Tile& b) {
    return a.price < b.price;
}
bool operator == (const Tile& a, const Tile& b) {
    return a.price == b.price;
}

vector<Tile> back, front;
int n;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (cin >> n) {
        back.resize(n);
        front.resize(n);
        REP(i,n) cin >> back[i].price;
        REP(i,n) cin >> back[i].height;
        REP(i,n) back[i].id = i + 1;
        REP(i,n) cin >> front[i].price;
        REP(i,n) cin >> front[i].height;
        REP(i,n) front[i].id = i + 1;

        sort(ALL(back));
        sort(ALL(front));
        int iBack = -1, iFront = -1;
        set< pair<int,int> > sBack, sFront;
        vector<int> resBack, resFront;

        try {
            REP(i,n) {
                if (iBack < i) {
                    while (iBack + 1 < n && back[iBack + 1] == back[i]) {
                        ++iBack;
                        sBack.insert({back[iBack].height, back[iBack].id});
                    }
                }
                if (iFront < i) {
                    while (iFront + 1 < n && front[iFront + 1] == front[i]) {
                        ++iFront;
                        sFront.insert({front[iFront].height, front[iFront].id});
                    }
                }
//                DEBUG(i);
//                cout << "Back : "; for (auto p : sBack) cout << p.second << ' '; cout << endl;
//                cout << "Front: "; for (auto p : sFront) cout << p.second << ' '; cout << endl;

                if (iFront < iBack) {
                    auto itFront = sFront.begin();
                    resFront.push_back(itFront->second);
                    int minHeight = itFront->first;

                    auto itBack = sBack.lower_bound({minHeight + 1, 0});
                    if (itBack == sBack.end()) throw 1;

                    resBack.push_back(itBack->second);
                    sFront.erase(itFront);
                    sBack.erase(itBack);
                } else {
                    auto itBack = sBack.end(); --itBack;
                    resBack.push_back(itBack->second);
                    int maxHeight = itBack->first;

                    auto itFront = sFront.lower_bound({maxHeight, 0});
                    if (itFront == sFront.begin()) throw 1;
                    itFront--;

                    resFront.push_back(itFront->second);
                    sFront.erase(itFront);
                    sBack.erase(itBack);
                }
            }
            for (int x : resBack) cout << x << ' '; cout << endl;
            for (int x : resFront) cout << x << ' '; cout << endl;
        } catch (...) {
            cout << "impossible" << endl;
        }
    }
    return 0;
}
