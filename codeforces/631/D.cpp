
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
#define next next___
using namespace std;

const int MN = 200111;
int ns, nt, nr;
pair<int,char> s[MN], t[MN], r[MN];
int next[MN];

void compress(pair<int,char> s[], int& ns) {
    int n = 0;
    FOR(i,1,ns) {
        if (i == 1 || s[i].second != s[n].second) {
            s[++n] = s[i];
        }
        else {
            s[n].first += s[i].first;
        }
    }
    ns = n;
}

int solve1() {
    assert(nt == 1);
    int res = 0;
    FOR(i,1,ns) {
        if (s[i].second == t[1].second && s[i].first >= t[1].first) {
            res += s[i].first - t[1].first + 1;
        }
    }
    return res;
}

int solve2() {
    assert(nt == 2);
    int res = 0;
    FOR(i,1,ns-1) {
        if (s[i].second == t[1].second && s[i].first >= t[1].first
                && s[i+1].second == t[2].second && s[i+1].first >= t[2].first) {
            ++res;
        }
    }
    return res;
}

int solve() {
    if (nt == 1) return solve1();
    else if (nt == 2) return solve2();
    int res = 0;

    // first, we need to build KMP next array for t[2..nt-1]
    nr = nt - 2;
    FOR(i,1,nr) r[i] = t[i+1];

    int j = 0; next[1] = 0;
    FOR(i,2,nr) {
        while (j > 0 && r[i] != r[j+1]) j = next[j];
        if (r[i] == r[j+1]) ++j;
        next[i] = j;
    }

    // then match against s
    j = 0;
    FOR(i,1,ns) {
        while (j > 0 && s[i] != r[j+1]) j = next[j];
        if (s[i] == r[j+1]) ++j;

        if (j == nr) {
            int from = (i - nr + 1) - 1;
            int to = i + 1;
            if (from >= 1 && s[from].first >= t[1].first && s[from].second == t[1].second
                    && to <= ns && s[to].first >= t[nt].first && s[to].second == t[nt].second)
                ++res;
            j = next[j];
        }
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> ns >> nt) {
        FOR(i,1,ns) {
            char tmp;
            cin >> s[i].first >> tmp >> s[i].second;
        }
        FOR(i,1,nt) {
            char tmp;
            cin >> t[i].first >> tmp >> t[i].second;
        }
        compress(s, ns);
        compress(t, nt);

//        FOR(i,1,ns) cout << s[i].first << '*' << s[i].second << ' '; cout << endl;
//        FOR(i,1,nt) cout << t[i].first << '*' << t[i].second << ' '; cout << endl;

        cout << solve() << endl;
    }
}
