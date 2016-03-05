
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

const int MN = 200111;
int n, q, a[MN], res[MN];
pair<int,int> queries[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,1,q) scanf("%d%d", &queries[i].first, &queries[i].second);

        vector<pair<int,int> > qq;
        int ln = 0;
        FORD(i,q,1) {
            if (queries[i].second > ln) {
                ln = queries[i].second;
                qq.push_back(queries[i]);
            }
        }
        reverse(qq.begin(), qq.end());
//        cout << "----------" << endl;
//        for(auto p : qq) cout << p.first << ' ' << p.second << endl;

        int lastPos = n, lastOrder = 0;

        multiset<int> all;
        FOR(i,1,n) all.insert(a[i]);

        qq.push_back(make_pair(1, 0));

        for(auto p : qq) {
            int from = p.second + 1;
            FORD(i,lastPos,from) {
                if (lastOrder == 0) res[i] = a[i];
                else if (lastOrder == 1) res[i] = *all.rbegin();
                else res[i] = *all.begin();

                all.erase(all.find(res[i]));
            }
            
            lastOrder = p.first;
            lastPos = p.second;
        }
        FOR(i,1,n) printf("%d ", res[i]); puts("");
    }
}
