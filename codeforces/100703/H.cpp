
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
using namespace std;

const int MN = 100111;
const int SQRTN = 300;

int n, a[MN], cached[MN], precomp[MN];
vector<int> ls[MN], bigs;

void init() {
    REP(i,MN) ls[i].clear();
    bigs.clear();
    memset(cached, 0, sizeof cached);
    memset(precomp, 0, sizeof precomp);
}

int get(const vector<int>& a, int diff) {
    int last = -MN;
    int res = 0;
    for(int x : a) {
        if (x - last > diff) {
            ++res;
            last = x;
        }
    }
    return res;
}

int getBigDiff(const vector<int>& a, int diff) {
    int res = 1;
    int last = 0;
    while (last + 1 < a.size()) {
        if (a.back() <= a[last] + diff) {
            break;
        }
        else {
            int id = upper_bound(a.begin() + last, a.end(), a[last] + diff) - a.begin();
            ++res;
            last = id;
        }
    }
    return res;
}

void initSmallList() {
//    cerr << "initSmallList" << endl;
    REP(i,MN)
    if (!ls[i].empty()) {
        if (ls[i].size() <= SQRTN) {
//        if (ls[i].size() <= 0) {
//            DEBUG(i);
//            PR0(ls[i], ls[i].size());

            int L = ls[i].size();
            precomp[n+1]++;
            FOR(result,1,L) {
                int left = 1, right = n, res = n;
                while (left <= right) {
                    int mid = (left + right) >> 1;
                    if (get(ls[i], mid) <= result) {
                        res = mid;
                        right = mid - 1;
                    }
                    else left = mid + 1;
                }
//                cout << res << ' ';
                precomp[res-1]++;
            }
//            cout << endl;
        }
        else bigs.push_back(i);
    }
    FORD(i,n,1) precomp[i] += precomp[i+1];
//    PR(precomp, n);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        init();
        FOR(i,1,n) {
            cin >> a[i];
            ls[a[i]].push_back(i);
        }
        initSmallList();

        int q; cin >> q;
        while (q--) {
            int x; cin >> x;
            if (cached[x]) {
            }
            else {
                int res = precomp[x];

                // consider big arrays
                for(int value : bigs) {
                    if (x <= SQRTN) {
//                    if (x <= 0) {
                        res += get(ls[value], x);
                    }
                    else {
                        res += getBigDiff(ls[value], x);
                    }
                }
                cached[x] = res;
            }
            printf("%d ", cached[x]);
        }
        puts("");
    }
}

