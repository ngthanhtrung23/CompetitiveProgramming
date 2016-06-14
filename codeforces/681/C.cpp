
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

char tmp[1011];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int nq;
    while (GI(nq) == 1) {
        vector< pair<string,int> > res;

        multiset<int> q;
        while (nq--) {
            int x;
            scanf("%s %lld\n", &tmp[0], &x);

            if (tmp[0] == 'i') {
                q.insert(x);
                res.emplace_back("insert", x);
            }
            else if (tmp[0] == 'r') {
                if (q.empty()) {
                    res.emplace_back("insert", 1);
                }
                else {
                    q.erase(q.begin());
                }
                res.emplace_back("removeMin", -1);
            }
            else {
                while (!q.empty() && *q.begin() < x) {
                    q.erase(q.begin());
                    res.emplace_back("removeMin", -1);
                }

                if (q.empty()) {
                    q.insert(x);
                    res.emplace_back("insert", x);
                }
                else if (*q.begin() > x) {
                    q.insert(x);
                    res.emplace_back("insert", x);
                }

                res.emplace_back("getMin", x);
            }
        }

        printf("%lld\n", SZ(res));
        for(auto p : res) {
            if (p.first[0] == 'r') printf("%s\n", p.first.c_str());
            else printf("%s %lld\n", p.first.c_str(), p.second);
        }
    }
}
