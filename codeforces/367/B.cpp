
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

#define next next__

const int MN = 200111;

int a[MN], b[MN], next[MN];
int na, nb, p;
vector<int> res;

map<int,int> need, has;
int bad, sz_need;

void add(int x, int val) {
    if (has[x] == need[x]) ++bad;
    has[x] += val;
    if (has[x] == need[x]) --bad;
}

void solve(vector<int>& x, vector<int>& ids) {
    int nx = SZ(x) - 1;
    int j = 0;

    bad = sz_need;
    has.clear();

    FOR(i,1,nx - nb + 1) {
        if (i > 1) {
            add(x[i-1], -1);
        }
        int to = i + nb - 1;
        while (j < to) {
            ++j;
            add(x[j], +1);
        }

        if (bad == 0) {
            res.push_back(ids[i]);
        }
    }
}

int main() {
    while (scanf("%d%d%d", &na, &nb, &p) == 3) {
        FOR(i,1,na) scanf("%d", &a[i]);
        FOR(i,1,nb) scanf("%d", &b[i]);

        need.clear();
        has.clear();

        FOR(i,1,nb) need[b[i]] += 1;
        sz_need = SZ(need);

        res.clear();
        FOR(start,1,p) {
            vector<int> x;
            vector<int> ids;

            x.push_back(0);
            ids.push_back(0);  // I like numbering from 1

            for(int i = start; i <= na; i += p) {
                x.push_back(a[i]);
                ids.push_back(i);
            }
//            PR(x, SZ(x)-1);

            solve(x, ids);
        }
        sort(res.begin(), res.end());
        printf("%d\n", SZ(res));
        for(int x : res) printf("%d ", x); puts("");
    }
}
