#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
long long X, k;
vector<long long> divs;
vector<long long> divDivs[MN];

vector<int> get(long long k) {
    if (k == 0) {
        vector<int> res(divs.size());
        REP(i,res.size()) res[i] = i;
        return res;
    }
    else if (k % 2 == 1) {
        vector<int> cur = get(k-1);
        vector<int> res;
        for(int x : cur) {
            int need = min(100000 - res.size(), divDivs[x].size());
            REP(turn,need)
                res.push_back(divDivs[x][turn]);
            if (res.size() == 100000) break;
        }
        return res;
    }
    else {
        vector<int> cur = get(k / 2);
        vector<int> res;
        vector<int> pos(divs.size(), -1);
        REP(i,cur.size())
            if (pos[cur[i]] < 0) pos[cur[i]] = i;
        REP(i,cur.size()) {
            if (cur[i] == 0) res.push_back(0);
            else {
                int from = pos[cur[i]-1] + 1, to = pos[cur[i]];
                int add = min(to - from + 1, 100000 - (int)res.size());
                REP(turn,add)
                    res.push_back(cur[from + turn]);
            }
            if (res.size() == 100000) break;
        }
        return res;
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> X >> k) {
        divs.clear();
        for(long long i = 1; i * i <= X; ++i) if (X % i == 0) {
            divs.push_back(i);
            if (i * i != X) divs.push_back(X / i);
        }
        sort(divs.begin(), divs.end());
//        PR0(divs, divs.size());
        REP(i,divs.size()) {
            divDivs[i].clear();
            REP(j,divs.size())
                if (divs[i] % divs[j] == 0)
                    divDivs[i].push_back(j);
//            DEBUG(divs[i]);
//            PR0(divDivs[i], divDivs[i].size());
        }
        if (k == 0) {
            cout << X << endl;
            continue;
        }
        vector<int> res = get(k - 1);
//        DEBUG("DONE");
        for(int x : res)
            cout << divs[x] << ' ';
        cout << endl;
    }
    return 0;
}

