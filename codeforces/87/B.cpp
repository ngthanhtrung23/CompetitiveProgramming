
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

struct Type {
    string core;
    int nStar;
    int nAmp;

    string to_string() const {
        if (core[0] == 'e') return core;
        else {
            string res = "";
            REP(turn,nAmp) res += '&';
            res += core;
            REP(turn,nStar) res += '*';
            return res;
        }
    }
};
map<string,Type> types;

Type parse(const string& s) {
    Type res;
    int start = 0;
    while (s[start] == '&') ++start;
    res.nAmp = start;

    int last = s.size()-1;
    while (s[last] == '*') --last;
    res.nStar = s.size() - 1 - last;

    int reduce = min(res.nStar, res.nAmp);
    res.nStar -= reduce;
    res.nAmp -= reduce;

    string core = s.substr(start, last - start + 1);
    if (core == "errtype") res.core = "errtype";
    else if (core == "void") {
        if (res.nAmp) res.core = "errtype";
        else res.core = "void";
    }
    else if (!types.count(core)) {
        res.core = "errtype";
    }
    else {
        auto that = types[core];
        if (that.core == "errtype") res.core = "errtype";
        else {
            res.core = that.core;
            res.nStar += that.nStar;
            res.nAmp += that.nAmp;

//            cout << "Parse: " << s << " --> " << core << endl;

            int reduce = min(res.nStar, res.nAmp);
            res.nStar -= reduce;
            res.nAmp -= reduce;

            if (res.nAmp) {
                res.core = "errtype";
            }
        }
    }
//    cout << "Parse " << s << ": " << res.nAmp << ' ' << res.core << ' ' << res.nStar << endl;
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        types.clear();
        while (n--) {
            string q; cin >> q;
            if (q[4] == 'o') {
                string a; cin >> a;
                auto typ = parse(a);
                cout << typ.to_string() << '\n';
            }
            else {
                string a, b; cin >> a >> b;
                auto typ = parse(a);
                types[b] = typ;
            }
        }
    }
    return 0;
}

