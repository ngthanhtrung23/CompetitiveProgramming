
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int cnt[11];
int f[10111000];

int value(string s) {
    memset(cnt, 0, sizeof cnt);
    int last = -1;
    REP(i,SZ(s)) {
        if (s[i] == '.') {
            ++last;
            ++cnt[last];
        }
        else {
            assert(s[i] == 'R');
            ++i;
            int cur = -1;
            if (s[i] == '2') cur = 1;
            else if (s[i] == '4') cur = 2;
            else if (s[i] == '8') cur = 3;
            else if (s[i] == '3') ++i, cur = 5;
            else if (s[i] == '6') ++i, cur = 6;
            else {
                assert(s[i] == '1');
                if (i+1 < SZ(s) && s[i+1] == '6') {
                    ++i;
                    cur = 4;
                }
                else cur = 0;
            }
            ++cnt[cur];
            last = cur;
        }
    }
    int res = 0;
    int mult = 1;
    FORD(i,6,0) {
        res += mult * cnt[i];
        mult *= 2;
    }
    return res;
}
vector< pair<int, string> > all;

void update(int& x, int val) {
    x = min(x, val);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("e.in", "r", stdin);
    freopen("e.out", "w", stdout);
    REP(i,7) {
        FOR(dot,0,6-i) {
            stringstream ss; ss << 'R' << (1<<i);
            REP(turn,dot) ss << '.';
            string s = ss.str();
            all.push_back(make_pair(value(s), s));
        }
    }
    sort(all.begin(), all.end());
    string s;
    while (cin >> s) {
        string res = "";
        int need = value(s);
        f[0] = 0;

        FOR(i,1,need) {
            if (i > 64*64) {
                f[i] = f[i-64] + 2;
                continue;
            }
            f[i] = 1e9;
            for(auto p : all) {
                if (i >= p.first) {
                    f[i] = min(f[i], f[i - p.first] + SZ(p.second));
                }
            }
        }

        while (need > 0) {
            string best = "XXX";
            int best_val = -1;
            string best_s = "";

            int minf = f[need];
            for(auto p : all) {
                if (p.first > need) continue;
                int cur = SZ(p.second) + f[need - p.first];
                if (cur > minf) continue;

                string t = p.second;
                if (p.first != need) t += 'R';
                if (t < best) {
                    best = t;
                    best_val = p.first;
                    best_s = p.second;
                }
            }
            res += best_s;
            need -= best_val;
        }
        puts(res.c_str());
    }
}
