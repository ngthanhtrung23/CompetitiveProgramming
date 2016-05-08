#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(int& x) {
    return scanf("%d", &x);
}

#define next next____
#define hash hash____
//int next[17000111];

ll hash(string s) {
    ll res = 0;
    for(char c : s) {
        res = res * 311 + c;
    }
    return res;
}

vector<pair<int,int> > bad;
bool check(const string& s, int l, int n) {
    for(auto b : bad) {
        if (l % b.first == 0 && l < b.second) {
            return false;
        }
    }

    FOR(i,l+1,n) if (s[i] != s[i-l]) {
        bad.emplace_back(l, i);
        return false;
    }
    return true;
}

char tmp[100011], x[311], y[311];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (GI(n) == 1) {
        bad.clear();

        map<ll,string> a;
        FOR(i,1,n) {
            scanf("%s", &x[0]);
            scanf("%s", &y[0]);

            a[hash(string(x))] = string(y);
        }
        string s = " ", t;
        while (scanf("%s", &tmp[0]) == 1) {
            t = string(tmp);
            if (t == "END") break;

            s += a[hash(t)];
        }

        int n = SZ(s) - 1;
        FOR(l,1,n) if (n % l == 0 && check(s, l, n)) {
            cout << l << endl;
            break;
        }

        /*
        int j = 0;
        next[1] = 0;
        FOR(i,2,n) {
            while (j > 0 && s[j+1] != s[i]) j = next[j];
            if (s[j+1] == s[i]) ++j;
            next[i] = j;
        }

        int r = next[n];
        while (n % (n - r)) r = next[r];
        cout << n - r << endl;
        */
    }
}
