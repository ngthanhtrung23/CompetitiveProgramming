
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << card[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << card[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

string card[55];
int n;

bool check(string a, string b) {
    return a[0] == b[0] || a[1] == b[1];
}
bool check(string a, string b, string c) {
    return check(c, b) && check(c, a);
}

set< pair< pair<int,string>, pair<string,string> > > s;
bool solve() {
    if (n == 1) return true;
    if (n == 2) return check(card[1], card[2]);

    queue<int> qn;
    queue<string> qa;
    queue<string> qb;
    queue<string> qc;
    s.clear();

    qn.push(n);
    qa.push(card[n-2]);
    qb.push(card[n-1]);
    qc.push(card[n]);
    s.insert(make_pair(make_pair(n, card[n-2]), make_pair(card[n-1], card[n])));
    while (!qn.empty()) {
        int n = qn.front(); qn.pop();
        string a = qa.front(); qa.pop();
        string b = qb.front(); qb.pop();
        string c = qc.front(); qc.pop();

        if (n == 3) {
            if (check(a, b, c)) return true;
            continue;
        }

        // c --> b
        string prev = card[n-3];
        if (check(c, b) && !s.count(make_pair(make_pair(n-1, prev), make_pair(a, c)))) {
            s.insert(make_pair(make_pair(n-1, prev), make_pair(a, c)));
            qn.push(n-1);
            qa.push(prev);
            qb.push(a);
            qc.push(c);
        }
        // c --> prev
        if (check(c, prev) && !s.count(make_pair(make_pair(n-1, c), make_pair(a, b)))) {
            s.insert(make_pair(make_pair(n-1, c), make_pair(a, b)));
            qn.push(n-1);
            qa.push(c);
            qb.push(a);
            qc.push(b);
        }
    }

    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> card[i];
        cout << (solve() ? "YES" : "NO") << endl;
    }
}
