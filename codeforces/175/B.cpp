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

vector< pair<int,string> > a;

int better(int x) {
    if (a[0].first > x) return a.size();
    if (a.back().first <= x) return 0;
    return a.end() - upper_bound(a.begin(), a.end(), make_pair(x+1, string("")));
}

int lower_equal(int x) {
    if (a.back().first <= x) return a.size();
    if (a[0].first > x) return 0;
    return upper_bound(a.begin(), a.end(), make_pair(x+1, string(""))) - a.begin();
}

int atleast(int x, int p) {
    return x*100 >= a.size() * p;
}

int morethan(int x, int p) {
    return x*100 > a.size()*p;
}

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        map<string,int> scores;
        string name; int x;
        while (cin >> name >> x) {
            scores[name] = max(scores[name], x);
        }
        a.clear();
        for(auto x : scores) a.push_back(make_pair(x.second, x.first));
        sort(a.begin(), a.end());
//        for(auto x : a) cout << x.first << ' ' << x.second << endl;

        vector< pair<string,string> > res;
        for(auto x : a) {
            if (morethan(better(x.first), 50))
                res.push_back(make_pair(x.second, "noob"));
            if (atleast(lower_equal(x.first), 50) && morethan(better(x.first), 20))
                res.push_back(make_pair(x.second, "random"));
            if (atleast(lower_equal(x.first), 80) && morethan(better(x.first), 10))
                res.push_back(make_pair(x.second, "average"));
            if (atleast(lower_equal(x.first), 90) && morethan(better(x.first), 1))
                res.push_back(make_pair(x.second, "hardcore"));
            if (atleast(lower_equal(x.first), 99))
                res.push_back(make_pair(x.second, "pro"));
        }
        cout << res.size() << endl;
        for(auto x : res) {
            cout << x.first << ' ' << x.second << endl;
        }
    }
    return 0;
}

