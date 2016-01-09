
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;

const int NX = 24;
pair<string,int> X[NX] = {
    {"DCCC", 800},
    {"DCC",  700},
    {"CCC",  300},
    {"CM",   900},
    {"DC",   600},
    {"CC",   200},
    {"D",    500},
    {"C",    100},

    {"LXXX", 80},
    {"LXX",  70},
    {"XXX",  30},
    {"XC",   90},
    {"LX",   60},
    {"XX",   20},
    {"L",    50},
    {"X",    10},

    {"VIII", 8},
    {"VII",  7},
    {"III",  3},
    {"IX",   9},
    {"VI",   6},
    {"II",   2},
    {"V",    5},
    {"I",    1},
};

int cnt[333];
int need[333];

bool can(const string& s) {
    bool res = true;
    for(char c : s) {
        ++need[c];
        if (need[c] > cnt[c]) res = false;
    }
    for(char c : s) need[c] = 0;
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    string s;
    while (cin >> s) {
        REP(i,SZ(s)) if (s[i] >= 'a' && s[i] <= 'z') s[i] ^= ' ';
        memset(cnt, 0, sizeof cnt);
        for(char c : s) cnt[c] ++;

        REP(turn,min(3,cnt['M'])) {
            cout << 'M';
            cnt['M'] --;
        }

        FOR(i,0,7) {
            if (can(X[i].first)) {
                cout << X[i].first;
                for(char c : X[i].first) cnt[c]--;
                break;
            }
        }
        FOR(i,8,15) {
            if (can(X[i].first)) {
                cout << X[i].first;
                for(char c : X[i].first) cnt[c]--;
                break;
            }
        }
        FOR(i,16,23) {
            if (can(X[i].first)) {
                cout << X[i].first;
                for(char c : X[i].first) cnt[c]--;
                break;
            }
        }
        cout << endl;
    }
}
