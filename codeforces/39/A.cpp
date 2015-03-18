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

const int MN = 1011;
pair<int,int> summands[MN];
int nSummand;

int main() {
    ios :: sync_with_stdio(false);
    int cur = 1;
    while (cin >> cur) {
        string s; cin >> s;
        int i = 0;
        int sign = 1;
        nSummand = 0;
        
        while (i < s.length()) {
            int coeff = 1;
            if (s[i] >= '0' && s[i] <= '9') {
                coeff = 0;
                while (s[i] >= '0' && s[i] <= '9') {
                    coeff = coeff * 10 + s[i] - '0';
                    ++i;
                }
                assert(s[i] == '*');
                ++i;
            }
            if (s[i] == 'a') {
                summands[++nSummand] = make_pair(sign * coeff, 0);
                assert(s[i] == 'a');
                assert(s[i+1] == '+');
                assert(s[i+2] == '+');
                i += 3;
            }
            else {
                summands[++nSummand] = make_pair(sign * coeff, 1);
                assert(s[i] == '+');
                assert(s[i+1] == '+');
                assert(s[i+2] == 'a');
                i += 3;
            }
            if (i == s.length()) break;
            assert(s[i] == '-' || s[i] == '+');
            if (s[i] == '-') sign = -1;
            else sign = 1;
            ++i;
        }
//        DEBUG(nSummand);
//        FOR(i,1,nSummand) cout << summands[i].first << ' ' << summands[i].second << endl;
        sort(summands+1, summands+nSummand+1);

        long long res = 0;
        FOR(i,1,nSummand) {
            if (summands[i].second == 1) ++cur;
            res += summands[i].first * (long long) cur;
            if (summands[i].second == 0) ++cur;
        }
        cout << res << endl;
    }
    return 0;
}
