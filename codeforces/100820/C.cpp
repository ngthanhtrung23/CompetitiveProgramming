
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

const int MN = 1011;

struct Person {
    vector<int> x;
    string name;
} a[MN];

bool operator < (const Person& a, const Person& b) {
    int l = min(SZ(a.x), SZ(b.x));
    REP(i,l) {
        if (a.x[i] < b.x[i]) return true;
        if (a.x[i] > b.x[i]) return false;
    }
    return a.name < b.name;
}

int val(string t) {
    if (t == "upper") return 0;
    if (t == "middle") return 1;
    if (t == "lower") return 2;
    assert(0);
    return -1;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n;
    while (cin >> n) {
        int ln = 0;
        FOR(i,1,n) {
            cin >> a[i].name;
            a[i].name = a[i].name.substr(0, SZ(a[i].name) - 1);

            a[i].x.clear();

            string t = ""; cin >> t;
            while (t != "class") {
                a[i].x.push_back(val(t));
                cin >> t;
            }
            reverse(a[i].x.begin(), a[i].x.end());

            ln = max(ln, SZ(a[i].x));
        }
        FOR(i,1,n) {
            while (SZ(a[i].x) < ln) a[i].x.push_back(1);
        }

        sort(a+1, a+n+1);

        FOR(i,1,n) cout << a[i].name << '\n';
        cout << endl;
    }
}
