
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

const int MN = 1000111;

int n;
pair<int,int> a[MN], b[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            scanf("%d", &a[i].first);
            a[i].second = i;
        }
        FOR(i,1,n) {
            scanf("%d", &b[i].first);
            b[i].second = i;
        }
        try {
            while (true) {
                map< int, pair<int,int> > id;
                id[0] = make_pair(0, 0);
                int ia = 0, ib = 0;
                int diff = 0;

                while (ia < n || ib < n) {
                    if (ia == n) {
                        diff -= b[++ib].first;
                    }
                    else if (ib == n) {
                        diff += a[++ia].first;
                    }
                    else if (diff <= 0) {
                        diff += a[++ia].first;
                    }
                    else {
                        diff -= b[++ib].first;
                    }

                    if (id.count(diff)) {
                        int ja = id[diff].first;
                        int jb = id[diff].second;

                        printf("%d\n", ia - ja);
                        FOR(x,ja+1,ia) printf("%d ", a[x].second); puts("");
                        printf("%d\n", ib - jb);
                        FOR(x,jb+1,ib) printf("%d ", b[x].second); puts("");
                        puts("");

                        throw 1;
                    }
                    id[diff] = make_pair(ia, ib);
                }

                random_shuffle(a+1, a+n+1);
                random_shuffle(b+1, b+n+1);
            }
        } catch (int e) {
        }
    }
}
