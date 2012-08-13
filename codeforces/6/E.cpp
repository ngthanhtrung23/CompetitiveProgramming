#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);
const int MN = 100111;

int a[MN], n, k;
multiset<int> s;
vector< pair<int,int> > save;

int main() {
    while (scanf("%d%d", &n, &k) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);
        s.clear();

        int j = 0, res = 0;
        save.clear();
        FOR(i,1,n) {
            if (i > 1) s.erase(s.find(a[i-1]));
            if (j < i) {
                ++j;
                s.insert(a[j]);
            }
            while (j < n && *(--s.end()) - *s.begin() <= k) {
                ++j;
                s.insert(a[j]);
            }
            if (*(--s.end()) - *s.begin() > k) {
                s.erase(s.find(a[j]));
                --j;
            }

            if (j-i+1 > res) {
                res = j - i + 1;
                save.clear();
                save.PB(MP(i,j));
            }
            else if (j - i + 1 == res) save.PB(MP(i,j));
        }
        printf("%d %d\n", res, save.size());
        REP(t,save.size())
            printf("%d %d\n", save[t].F, save[t].S);
    }
    return 0;
}
