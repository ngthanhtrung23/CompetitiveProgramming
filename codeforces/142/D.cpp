
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int n, m, k;
char a[111][111];

int main() {
    while (cin >> m >> n >> k) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        if (n == 1) cout << "Second" << endl;
        else if (n == 2) {
            bool can1 = false, can2 = false;
            FOR(i,1,m) if (a[i][1] == '-' || a[i][2] == '-') {
                if (a[i][1] == 'G' || a[i][2] == 'G') can1 = true;
                if (a[i][1] == 'R' || a[i][2] == 'R') can2 = true;
            }
            if (!can1) cout << "Second" << endl;
            else if (can2) cout << "Draw" << endl;
            else cout << "First" << endl;
        }
        else {
            bool can1 = false, can2 = false;
            FOR(i,1,m) {
                int cnt = 0;
                int sum = 0;
                FOR(j,1,n) if (a[i][j] == 'R' || a[i][j] == 'G') {
                    ++cnt;
                    sum += a[i][j];
                }
                if (cnt) {
                    if (sum == cnt * 'G') can1 = true;
                    else if (sum == cnt * 'R') can2 = true;
                }
            }
            if (can1 && can2) cout << "Draw" << endl;
            else if (can1) cout << "First" << endl;
            else if (can2) cout << "Second" << endl;
            else {
                vector<int> x;
                FOR(i,1,m) {
                    int cnt = 0;
                    int first = -1, second = -1;
                    FOR(j,1,n) if (a[i][j] == 'R' || a[i][j] == 'G') {
                        ++cnt;
                        if (cnt == 1) first = j;
                        else second = j;
                    }
                    if (cnt == 2) x.push_back(second - first - 1);
                }
                bool good = true;
                REP(bit,10) {
                    int cnt = 0;
                    for(int cur : x) {
                        if (cur & (1<<bit))
                            ++cnt;
                    }
                    if (cnt % (k + 1)) {
                        good = false;
                        break;
                    }
                }
                if (good) cout << "Second" << endl;
                else cout << "First" << endl;
            }
        }
    }
    return 0;
}

