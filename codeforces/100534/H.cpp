#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

vector< pair<int, pair<int,int> > > all;

int mysqrt(int x) {
    int a = sqrt(x);
    while (a * a < x) ++a;
    while (a * a > x) --a;
    return a;
}

int S, P;
#define sqr(x) ((x) * (x))
bool check(int x1, int y1, int x2, int y2, int c) {
    if (c*c == sqr(x1-x2) + sqr(y1-y2)) {
        cout << "Dream" << endl << 0 << ' ' << 0 << endl << x1 << ' ' << y1 << endl << x2 << ' ' << y2 << endl;
        return true;
    }
    return false;
}

void solve() {
    long long prod = S * (long long) S / (P/2);
    FOR(a,1,P/2-1) if (prod % (P/2 - a) == 0) FOR(b,1,P-a-1) {
        int c = P - a - b;
        if (c < 0 || c > P) continue;
        
        long long p = P / 2;
        if (S * (long long) S / 4 != p * (p-a) * (p-b) * (p-c)) continue;

        int ia = lower_bound(all.begin(), all.end(), make_pair(a, make_pair(0, 0))) - all.begin();
        int ib = lower_bound(all.begin(), all.end(), make_pair(b, make_pair(0, 0))) - all.begin();
        int saveib = ib;

        while (all[ia].first == a) {
            ib = saveib;
            while (all[ib].first == b) {
                int x = all[ia].second.first, y = all[ia].second.second, z = all[ib].second.first, t = all[ib].second.second;
                REP(turn,2) {
                    REP(turn2,2) {
                        REP(turn1,2) {
                            if (check(x, y, z, t, c)) return ;
                            if (check(x, y, -z, t, c)) return ;
                            if (check(x, y, z, -t, c)) return ;
                            if (check(x, y, -z, -t, c)) return ;
                            swap(z, t);
                        }
                        swap(x, y);
                    }
                    swap(x, z);
                    swap(y, t);
                }
                ++ib; if (ib == all.size()) break;
            }
            ++ia; if (ia == all.size()) break;
        }
    }
    cout << "Flag" << endl;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    FOR(i,1,10000) FOR(j,i+1,10000) {
        int cur = i*i + j*j;
        int k = mysqrt(cur);
        if (k*k == cur) all.push_back(make_pair(k, make_pair(i, j)));
    }
    FOR(i,1,10000) all.push_back(make_pair(i, make_pair(0, i)));
    sort(all.begin(), all.end());
    while (cin >> S >> P) {
        if (S % 2 == 1) cout << "Flag" << endl;
        else if (P % 2 == 1) cout << "Flag" << endl;
        else if (S *(long long) S % (P/2)) cout << "Flag" << endl;
        else solve();
    }
    return 0;
}

