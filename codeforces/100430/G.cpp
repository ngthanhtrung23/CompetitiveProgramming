
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 100111;

int n, a[MN];

ll getSum() {
    ll res = 0;
    FOR(i,1,n) res += a[i];
    return res;
}

int getMax() {
    return *max_element(a+1, a+n+1);
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);

    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        ll sum = getSum();
        int ln = getMax();

        if (sum % 2 == 1 && ln > sum - ln) {
            FOR(i,1,n) if (a[i] == ln) --a[i];
        }

        sum = getSum();
        ln = getMax();
        if (ln > sum - ln) {
            FOR(i,1,n) if (a[i] == ln) {
                a[i] -= (2*ln - sum);
                break;
            }
        }

        sum = getSum();
        if (sum % 2 == 1) --sum;

//        PR(a, n);

        set< pair<int,int> > all;
        set< pair<int,int> > greatest;

        FOR(i,1,n) {
            all.insert(make_pair(i, a[i]));
            greatest.insert(make_pair(a[i], i));
        }
        sum = 0;
        FOR(i,1,n) sum += a[i];

        vector< pair< pair<int,int>, int > > res;
        while (all.size() > 1) {
            auto x = *all.begin(); all.erase(all.begin());
            auto y = *all.begin(); all.erase(all.begin());

            greatest.erase(make_pair(x.second, x.first));
            greatest.erase(make_pair(y.second, y.first));

            int cur = min(x.second, y.second);
            sum -= 2*cur;

            if (!greatest.empty()) {
                auto it = greatest.end(); --it;
                int ln = it->first;
                if (ln > sum - ln) {
                    ll bad = ln - (sum - ln);
                    cur -= bad / 2;
                    if (cur) res.push_back(make_pair(make_pair(x.first, y.first), cur));

                    int id = it->second;
                    greatest.erase(it);

                    x.second -= cur;
                    y.second -= cur;

                    if (x.second) res.push_back(make_pair(make_pair(x.first, id), x.second));
                    if (y.second) res.push_back(make_pair(make_pair(y.first, id), y.second));

                    for(auto p : greatest) {
                        if (p.first)
                            res.push_back(make_pair(make_pair(p.second, id), p.first));
                    }
                    break;
                }
            }

            // ok, can proceed
            x.second -= cur;
            y.second -= cur;

            res.push_back(make_pair(make_pair(x.first, y.first), cur));

            if (x.second > 0) all.insert(x);
            greatest.insert(make_pair(x.second, x.first));
            if (y.second > 0) all.insert(y);
            greatest.insert(make_pair(y.second, y.first));
        }
        REP(i,res.size())
            if (res[i].first.first > res[i].first.second)
                swap(res[i].first.first, res[i].first.second);
        sort(res.begin(), res.end());

        cout << res.size() << '\n';
        REP(i,res.size()-1) assert(res[i].first != res[i+1].first);
        for(auto p : res) cout << p.first.first << ' ' << p.first.second << ' ' << p.second << '\n';
        cout << endl;
    }
}

