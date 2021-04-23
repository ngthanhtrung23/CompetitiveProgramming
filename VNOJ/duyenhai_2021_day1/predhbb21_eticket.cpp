#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

// 1..n
//
// i-1......i-2
//    i......i-1
//
// - if string i-1 --> i --> update string
//
// - if s[i-1] != '.' && s[i] != '.' --> update substring i...?
// - if s[i-1] != '.' --> remove substring(i, i)
// - if s[i] != '.' --> no change
//
// - if s[i] != '.' && s[i] != '.' --> update substring ?...i
// - if s[i] != '.' --> no change
// - if s[i+1] != '.' --> add substring (i, i)

const int MN = 2011;
set<string> dict;
string a[MN];
int nRow, nCol;

#define next jaklcjojojacj
#define prev jkascjkljlaj
int next[MN]; // next[i] = position of next '.'
int prev[MN];

#define PR(a) { cout << #a << " = "; for (auto x : a) cout << x << ' '; cout << endl; }

string getStr(const string& s, int from, int to) {
    if (from <= to) {
        return s.substr(from, to - from + 1);
    } else {
        return s.substr(from, nCol - from + 1)
            + s.substr(1, to);
    }
}

int plus1(int x) {
    if (x == nCol) return 1;
    return x + 1;
}

bitset<MN> solve(string s) {
    //cout << "s = " << s << endl;

    // init next
    next[nCol+1] = s.substr(1).find('.') + 1;
    for (int i = nCol; i >= 1; i--) {
        if (s[i] == '.') {
            next[i] = i;
        } else {
            next[i] = next[i+1];
        }
    }
    //{ cout << "next = "; for (int i = 1; i <= nCol; i++) cout << next[i] << ' '; cout << endl; }

    // init prev
    prev[0] = s.substr(0, SZ(s) - 1).rfind('.');
    for (int i = 1; i <= nCol; i++) {
        if (s[i] == '.') {
            prev[i] = i;
        } else {
            prev[i] = prev[i-1];
        }
    }
    //{ cout << "prev = "; for (int i = 1; i <= nCol; i++) cout << prev[i] << ' '; cout << endl; }

    //PR(cur);
    //cout << "cur_bad = " << cur_bad << endl;

    bitset<MN> res;
    res.reset();

    deque<string> cur;
    int cur_bad = 0;
    auto add_str = [&cur, &cur_bad] (const string& s) {
        if (!dict.count(s)) ++cur_bad;
        cur.push_back(s);
    };
    auto rem_str = [&cur, &cur_bad] (const string& s) {
        if (!dict.count(s)) --cur_bad;
        cur.pop_front();
    };
    auto mod_str = [&cur, &cur_bad] (const string& s, int id) {
        if (!dict.count(cur[id])) {
            --cur_bad;
        }
        if (!dict.count(s)) {
            ++cur_bad;
        }
        cur[id] = s;
    };

    // init current set of strings.
    string tmp = "";
    for (int i = 1; i <= nCol+1; i++) {
        if (s[i] == '.') {
            if (tmp != "") {
                add_str(tmp);
            }
            tmp = "";
        } else {
            tmp += s[i];
        }
    }
    if (cur_bad == 0) {
        res[1] = 1;
    }

    for (int l = 1, r = nCol; l < nCol; l = plus1(l), r = plus1(r)) {
        // cur: [l, r]
        // --> [l+1, r+1]

        int ll = plus1(l);
        int rr = plus1(r);

        if (s[l] != '.' && s[r] != '.' && SZ(cur) == 1) {
            mod_str(getStr(s, ll, rr), 0);
            continue;
        }

        if (s[l] != '.' && s[ll] != '.') {
            mod_str(getStr(s, ll, next[ll] - 1), 0);
        } else if (s[l] != '.') {
            rem_str(cur[0]);
        } else if (s[ll] != '.') {
        }

        if (s[r] != '.' && s[rr] != '.') {
            mod_str(getStr(s, plus1(prev[rr]), rr), SZ(cur) - 1);
        } else if (s[rr] != '.') {
            add_str(getStr(s, rr, rr));
        }

        //PR(cur);
        if (cur_bad == 0) res[ll] = 1;
    }

    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int nDict; cin >> nDict;
    while (nDict--) {
        string s; cin >> s;
        dict.insert(s);
    }

    cin >> nRow;
    for (int i = 1; i <= nRow; i++) {
        cin >> a[i];
        nCol = SZ(a[i]);
        a[i] = "." + a[i] + ".";
    }

    bitset<MN> res;
    for (int i = 1; i <= nCol; i++) {
        res[i] = 1;
    }

    for (int i = 1; i <= nRow; i++) {
        res = res & solve(a[i]);
    }
    cout << res.count() << endl;
    for (int i = 1; i <= nCol; i++) {
        if (res[i]) cout << i-1 << ' ';
    }
    cout << endl;
    return 0;
}
