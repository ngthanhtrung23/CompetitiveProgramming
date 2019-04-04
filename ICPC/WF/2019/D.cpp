/**
Problem:
- Given N string of type ei / si, arranged in a circle.
- Cut the circle at point P --> a line.
- i is good if all si / ei form a valid bracket sequence (s = '(', e = ')')
- Find P such that there are maximum number of good i

Solution:
- For each i, extract all si / ei.
- Find all cut positions such that i is good --> update these range
*/
#include "bits/stdc++.h"
using namespace std;

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

struct Item {
    int sign;
    int value;

    Item(const string& s) {
        stringstream ss(s);
        char c; ss >> c;
        sign = (c == 's' ? +1 : -1);
        ss >> value;
    }
};
ostream& operator << (ostream& cout, const Item& i) {
    cout << i.sign << ' ' << i.value;
    return cout;
}

vector< pair<int,int> > a[1000111];
int sum[2000111];
int res[1000111];
int n;

void add(int from, int to) {
    assert(from < n);
    assert(to < n);
    if (from <= to) {
        res[from]++;
        res[to+1]--;
    } else {
        add(from, n-1);
        add(0, to);
    }
}

void up(const vector< pair<int,int> >& a) {
    if (a.empty()) return;

    int n = SZ(a);
    FOR(i,1,n) {
        sum[i] = sum[i + n] = a[i-1].first;
    }
    FOR(i,1,2*n) {
        sum[i] += sum[i-1];
    }
    if (sum[2*n]) return;
//    PR(sum, 2*n);

    multiset<int> all;
    FOR(i,1,n) {
        all.insert(sum[i]);
    }

    FOR(i,1,n) {
        // Check if [i, i+n-1] is good.
        if (*all.begin() >= sum[i-1]) {
            int to = a[i-1].second;
            int from = (a[((i-2) + SZ(a)) % SZ(a)].second + 1) % ::n;

            add(from, to);
        }
        // Remove i
        all.erase(all.find(sum[i]));

        // Add i+n
        all.insert(sum[i+n]);
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    cin >> n;
    vector<Item> items;
    REP(i,n) {
        string s; cin >> s;
        items.emplace_back(s);
    }
    REP(i,n) {
        a[items[i].value].emplace_back(items[i].sign, i);
    }

    memset(res, 0, sizeof res);
    FOR(i,1,1000 * 1000) {
        up(a[i]);
    }
    FOR(i,1,n-1) res[i] += res[i-1];

    int ln = -1;
    int save = -1;
    FOR(i,0,n-1) {
        if (res[i] > ln) {
            ln = res[i];
            save = i;
        }
    }
    cout << save + 1 << ' ' << ln << endl;
    return 0;
}
