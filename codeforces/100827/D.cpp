
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

pair<int,int> t;
double a, b, c, d, r;
set< pair<int,int> > calculating;

pair<int,int> refine(pair<int,int> t) {
    if (t.second < 0) {
        t.second = -t.second;
        t.first = -t.first;
    }
    int g = __gcd(abs(t.first), abs(t.second));
    t.first /= g;
    t.second /= g;
    return t;
}

struct Result {
    int typ;   // 0 - exact, 1 - dependant
    double val;
    pair<int,int> t;
    double a, b;

    friend ostream& operator << (ostream& cout, Result& x) {
        if (x.typ == 0) {
            cout << "value(" << x.val << ")";
        }
        else {
            cout << x.a << "*z(" << x.t.first << '/' << x.t.second << ") + " << x.b;
        }
        return cout;
    }
};

Result f(pair<int,int> t) {
    t = refine(t);
    if (calculating.count(t)) {
        Result res;
        res.typ = 1;
        res.t = t;
        res.a = 1.0;
        res.b = 0.0;
        return res;
    }
    calculating.insert(t);

    pair<int,int> t2;
    if (t.first <= 0) {
        t2 = make_pair(
                -t.second - 2*t.first,
                t.second);
    }
    else {
        t2 = make_pair(
                t.second - 2*t.first,
                t.second);
    }
    t2 = refine(t2);

    double a = (t.first <= 0) ? ::a : ::c;
    double b = (t.first <= 0) ? ::b : ::d;
    double T = t.first / (double) t.second;

    Result zt2 = f(t2);
//    cout << "f(" << t.first << '/' << t.second << ")" << endl;
//    cout << "t2 = " << t2.first << '/' << t2.second << endl;
//    cout << "zt2 = " << zt2 << endl;

    if (zt2.typ == 0) {
        Result z;
        z.typ = 0;
        z.val = (a + (b+r*sqr(T)) * zt2.val) / r;
        return z;
    }

    if (zt2.t != t) {
        Result z;
        z.typ = 1;
        z.t = zt2.t;
        z.a = zt2.a * (b + r*sqr(T));
        z.b = zt2.b * (b + r*sqr(T)) + a;

        z.a /= r;
        z.b /= r;
        return z;
    }
    Result res;
    res.typ = 0;
    res.val = (a + (b + r*T*T) * zt2.b) / (r - (b + r*T*T) * zt2.a);
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        calculating.clear();
        cin >> t.first >> t.second >> a >> b >> c >> d >> r;
        t = refine(t);
        auto res = f(t);
        cout << res.val << endl;
    }
}
