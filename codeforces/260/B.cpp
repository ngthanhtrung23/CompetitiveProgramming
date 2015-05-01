
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
    string s;
    while (cin >> s) {
        int nDay[] = {0, 31, 28, 31, 30, 31, 30, 31, 
                        31, 30, 31, 30, 31};

        map<string, int> cnt;
        FOR(start,0,s.length()-10) {
            cnt[s.substr(start, 10)] += 1;
        }

        int best = 0; string save = "";
        FOR(year,2013,2015) FOR(month,1,12) FOR(day,1,nDay[month]) {
            char tmp[12];
            sprintf(tmp, "%02d-%02d-%d", day, month, year);

            string cur(tmp);
            if (cnt[cur] > best) {
                best = cnt[cur];
                save = cur;
            }
        }
        cout << save << endl;
    }
    return 0;
}
