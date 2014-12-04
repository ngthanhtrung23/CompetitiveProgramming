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

#define sqr(x) ((x) * (x))
long long maximize(long long n, long long ngroup, vector<int> &save, bool trace = false) {
    save.clear();
    long long res = sqr(n - ngroup + 1) + ngroup - 1;
    if (trace) {
        REP(turn,ngroup) {
            long long cur = 1;
            if (turn == 0) cur = cur = n - ngroup + 1;
            if (trace) save.push_back(cur);
        }
    }
    return res;
}

long long minimize(long long n, long long ngroup, vector<int> &save, bool trace = false) {
    save.clear();
    long long res = (n % ngroup) * sqr(n / ngroup + 1) + (ngroup - n % ngroup) * sqr(n / ngroup);
    if (trace) {
        REP(turn,ngroup) {
            long long cur = n / ngroup;
            if (turn < n % ngroup) cur += 1;
            
            if (trace) save.push_back(cur);
        }
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    long long a, b;
    while (cin >> a >> b) {
        long long res = -1000111000111LL;
        if (a == 0) {
            res = - b * b;
            cout << res << endl;
            FOR(i,1,b) cout << 'x';
            cout << endl;
            continue;
        }
        if (b == 0) {
            res = a * a;
            cout << res << endl;
            FOR(i,1,a) cout << 'o';
            cout << endl;
            continue;
        }
        vector<int> savea, saveb;
        long long savegroupa, savegroupb;
        FOR(groupa,1,a) FOR(groupb,groupa-1,groupa+1) {
            if (groupb < 1 || groupb > b) continue;
            if (groupa < 1 || groupa > a) continue;

            long long cur = maximize(a, groupa, savea) - minimize(b, groupb, saveb);
            if (cur > res) {
                res = cur;
                savegroupa = groupa;
                savegroupb = groupb;
            }
        }
        cout << res << endl;
        maximize(a, savegroupa, savea, true);
        minimize(b, savegroupb, saveb, true);
        if (savegroupa > savegroupb) {
            REP(turn,max(savegroupa, savegroupb)) {
                if (turn < savegroupa) {
                    int x = savea[turn];
                    while (x--) cout << 'o';
                }
                if (turn < savegroupb) {
                    int y = saveb[turn];
                    while (y--) cout << 'x';
                }
            }
        }
        else {
            REP(turn,max(savegroupa, savegroupb)) {
                if (turn < savegroupb) {
                    int y = saveb[turn];
                    while (y--) cout << 'x';
                }
                if (turn < savegroupa) {
                    int x = savea[turn];
                    while (x--) cout << 'o';
                }
            }
        }
        cout << endl;
    }
    return 0;
}

