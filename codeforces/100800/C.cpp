
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

set<string> user;
set< pair<string,string> > allPair;
map< string, pair<int,int > > cnt;
vector< pair<int,string> > res;

char tmp[2000111];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (scanf("%d\n", &n) == 1) {
        user.clear();
        allPair.clear();
        cnt.clear();
        res.clear();

        while (n--) {
            gets(tmp);
            stringstream ss(tmp);

            string user_name;
            ss >> user_name;

            user.insert(user_name);

            string t;
            while (ss >> t) {
                pair<int,int> cur = (cnt.count(t)) ? cnt[t] : make_pair(0, 0);

                if (allPair.count(make_pair(t, user_name))) {
                    cur.second += 1;
                } else {
                    allPair.insert(make_pair(t, user_name));
                    cur.first += 1;
                    cur.second += 1;
                }
                cnt[t] = cur;
            }
        }

        for(__typeof(cnt.begin()) it = cnt.begin(); it != cnt.end(); ++it)
            if (it->second.first == user.size()) {
                res.push_back(make_pair(-it->second.second, it->first));
            }

        if (res.empty()) {
            puts("ALL CLEAR");
            continue;
        }

        sort(res.begin(), res.end());
        REP(i,SZ(res)) puts(res[i].second.c_str());
    }
}

