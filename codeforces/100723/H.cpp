
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

string s;
int n;
map<ll,int> cnt[33][33][111];
map<ll,string> word[33][33][111];
int f[1011], trj[1011];
string tr[1011];
ll p101[1011];

#define hash hash__
ll hash(string s) {
    ll res = 0;
    FOR(i,1,SZ(s)-2) {
        int add = s[i] - 'a';
        res += p101[add];
    }

    return res;
}

void trace(int i) {
    if (i == 0) return ;
    trace(trj[i]);

    printf("%s ", tr[i].c_str());
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    p101[0] = 1;
    FOR(i,1,1000) p101[i] = p101[i-1] * 101LL;

    while (ntest--) {
        cin >> s;
        n = s.length();
        s = " " + s;

        FOR(start,0,'z'-'a')
            FOR(last,0,'z'-'a')
                FOR(len,1,100) {
                    cnt[start][last][len].clear();
                    word[start][last][len].clear();
                }
        memset(f, 0, sizeof f);
        f[0] = 1;

        int k; cin >> k;
        while (k--) {
            string t; cin >> t;
            int start = t[0] - 'a';
            int last = t.back() - 'a';
            int len = t.length();

            ll h = hash(t);
            cnt[start][last][len][h] += 1;
            word[start][last][len][h] = t;
        }

        FOR(i,1,n) {
            int last = s[i] - 'a';
            ll h = 0;
            FORD(j,i-1,0) {
                int start = s[j+1] - 'a';
                int len = i - j;

                if (j <= i-3) {
                    int add = s[j+2] - 'a';
                    h += p101[add];
                }

                int has = cnt[start][last][len][h];

                if (f[j] > 0 && has) {
                    f[i] += f[j] * has;
                    if (f[i] == 1) {
                        tr[i] = word[start][last][len][h];
                        trj[i] = j;
                    }
                }
            }
            if (f[i] > 2) f[i] = 2;
        }
        if (f[n] == 0) puts("impossible");
        else if (f[n] > 1) puts("ambiguous");
        else {
            trace(n);
            puts("");
        }
    }
}
