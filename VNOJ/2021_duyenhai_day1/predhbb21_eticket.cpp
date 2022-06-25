#include "bits/stdc++.h"
using namespace std;

#define DEBUG(X) { auto _X = (X); cout << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int nRow, nCol;
string s[2011];
set<int> dict;

#define next ajicoja
#define prev ascoiac
int next[2011][6011], prev[2011][6011];

const int MOD = 1e9 + 7;
const int BASE = 311;
int p[6011], p_inv[6011];
int h[2011][6011];

// O(log)
int power(int x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;

    int mid = power(x, k/2);
    mid = mid * (long long) mid % MOD;

    if (k % 2) return mid * (long long) x % MOD;
    return mid;
}
// O(log)
int inverse(int x) {
    return power(x, MOD - 2);
}

// O(|s|)
int getHash(const string& t) {
    int res = 0;
    for (int i = 0; i < SZ(t); i++) {
        res = (res + t[i] * (long long) p[i]) % MOD;
    }
    return res;
}

// O(1)
int getSubstrHash(int row, int from, int to) {
    assert(from >= 1 && to <= 6000);

    int res = (h[row][to] - h[row][from - 1] + MOD) % MOD;
    return res * (long long) p_inv[from] % MOD;
}

// O(M*N)
void initHash() {
    for (int row = 1; row <= nRow; row++) {
        h[row][0] = (s[row][0] * (long long) p[0]) % MOD;
        for (int i = 1; i <= 6000; i++) {
            h[row][i] = (h[row][i-1] + s[row][i] * (long long) p[i]) % MOD;
        }
    }
}

struct Store {
    deque<int> qu;
    int bad;

    Store() : bad(0) {}

    // O(log)
    void push_back(int t) {
        if (!dict.count(t)) {
            ++bad;
        }
        qu.push_back(t);
    }

    // O(log)
    void pop_front() {
        if (!dict.count(qu[0])) {
            --bad;
        }
        qu.pop_front();
    }

    // O(log)
    void modify(int t, int id) {
        if (!dict.count(qu[id])) {
            --bad;
        }
        if (!dict.count(t)) {
            ++bad;
        }
        qu[id] = t;
    }

    void print() {
        cout << "cur = ";
        for (auto tmp : qu) cout << "'" << tmp << "' ";
        cout << "; bad = " << bad << endl;
    }
};

int concatHash(int left, int right, int leftLength) {
    return (left + right * (long long) p[leftLength]) % MOD;
}

// O(1)
int getString(int row, int start, int limit) {
    int end = min(next[row][start] - 1, limit);

    int res = getSubstrHash(row, start, end);

    if (row < nRow && end == limit && s[row][limit] != '.') {
        int nextStart = limit + 1;
        if (s[row + 1][nextStart] != '.') {
            int nextEnd = min(next[row+1][nextStart] - 1, limit + nCol);
            int hashRight = getSubstrHash(row + 1, nextStart, nextEnd);

            return concatHash(res, hashRight, end - start + 1);
        }
    }
    if (row > 1 && start == limit - nCol + 1 && s[row][start] != '.') {
        int prevEnd = limit - nCol;
        if (s[row - 1][prevEnd] != '.') {
            return -1;
        }
    }
    return res;
}

bitset<2011> solve(int row) {
    // DEBUG(row);
    bitset<2011> res; res.reset();
    Store store;

    // init
    string tmp = "";
    int i = 1;
    while (i <= nCol) {
        if (s[row][i] == '.') {
            ++i;
            continue;
        }
        store.push_back(getString(row, i, nCol));
        i = min(nCol+1, next[row][i]);
    }

    // store.print();
    if (store.bad == 0) {
        res[1] = 1;
    }

    // rotate
    for (int l = 1, r = nCol; l < nCol; l++, r++) {
        int ll = l + 1;
        int rr = r + 1;

        if (SZ(store.qu) == 1 && s[row][l] != '.' && s[row][r] != '.') {
            store.modify(getString(row, ll, rr), 0);
            continue;
        }

        if (s[row][l] != '.' && s[row][ll] != '.') {
            store.modify(getString(row, ll, rr), 0);
        } else if (s[row][l] != '.') {
            store.pop_front();
        } else if (s[row][ll] != '.') {
            store.modify(getString(row, ll, rr), 0);
        }

        if (s[row][r] != '.' && s[row][rr] != '.') {
            int start = prev[row][rr] + 1;
            store.modify(getString(row, start, rr), SZ(store.qu) - 1);
        } else if (s[row][rr] != '.') {
            store.push_back(getString(row, rr, rr));
        } else if (s[row][r] != '.') {
            int start = prev[row][r] + 1;
            store.modify(getString(row, start, rr), SZ(store.qu) - 1);
        }

        if (store.bad == 0) res[ll] = 1;
    }
    // DEBUG(res[340]);
    // for (int i = 1; i <= nCol; i++) cout << res[i];
    // cout << endl;

    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);

    p[0] = 1;
    for (int i = 1; i <= 6000; i++) {
        p[i] = (p[i-1] * (long long) BASE) % MOD;
    }
    for (int i = 0; i <= 6000; i++) {
        p_inv[i] = inverse(p[i]);
    }

    int nDict;
    while (cin >> nDict) {
        dict.clear();
        while (nDict--) {
            string tmp; cin >> tmp;
            dict.insert(getHash(tmp));
        }
        dict.insert(-1);
        cin >> nRow;

        for (int i = 1; i <= nRow; i++) {
            cin >> s[i];
            nCol = SZ(s[i]);

            s[i] = "." + s[i] + s[i] + s[i] + ".";

            for (int j = nCol*3+1; j >= 1; j--) {
                if (s[i][j] == '.') next[i][j] = j;
                else next[i][j] = next[i][j+1];
            }
            for (int j = 0; j <= nCol*3; j++) {
                if (s[i][j] == '.') prev[i][j] = j;
                else prev[i][j] = prev[i][j-1];
            }
        }
        initHash();

        bitset<2011> res;
        res.reset();
        for (int i = 1; i <= nCol; i++) {
            res[i] = 1;
        }

        for (int row = 1; row <= nRow; row++) {
            res = res & solve(row);
        }

        cout << res.count() << endl;
        for (int i = 1; i <= nCol; i++) {
            if (res[i] == 1) {
                cout << i - 1 << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}
