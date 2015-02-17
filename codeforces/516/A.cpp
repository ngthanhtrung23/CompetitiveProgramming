
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

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n; string s;
    map< char, vector<int> > ls;
    ls['2'] = {2};
    ls['3'] = {3};
    ls['4'] = {3, 2, 2};
    ls['5'] = {5};
    ls['6'] = {5, 3};
    ls['7'] = {7};
    ls['8'] = {7, 2, 2, 2};
    ls['9'] = {7, 2, 3, 3};

    while (cin >> n >> s) {
        vector<int> digits;
        for(char c : s) {
            if (ls.count(c)) {
                for(int u : ls[c])
                    digits.push_back(u);
            }
        }
        sort(digits.begin(), digits.end());
        reverse(digits.begin(), digits.end());
        for(int x : digits) cout << x; cout << endl;
    }
    return 0;
}
