#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
// On CF, GNU C++ seems to have some precision issues with long double?
// #define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define stat akjcjalsjcjalscj
#define hash ajkscjlsjclajsc
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (((S) >> (X)) & 1)

long long rand16() {
    return rand() & (TWO(16) - 1);
}
long long my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(long long& x) { return scanf("%lld", &x); }

using Row = std::array<int, 9>;
using Board = std::array<Row, 9>;

Board candidates, board;  // candidates = bitmask containing all possible values

char getChar() {
    char c = ' ';
    while (c < '0' || c > '9') cin >> c;
    return c;
}

void removeBitIfExists(int& mask, int bit) {
    if (CONTAIN(mask, bit)) {
        mask -= TWO(bit);
    }
}

bool inside(int r, int c) {
    return 0 <= r && r < 9
        && 0 <= c && c < 9;
}

void setValue(int r, int c, int value) {
    assert(1 <= value && value <= 9);
    assert(inside(r, c));
    assert(CONTAIN(candidates[r][c], value - 1));

    board[r][c] = value;

    // remove candidates from same row
    REP(c2,9) if (c2 != c) {
        removeBitIfExists(candidates[r][c2], value - 1);
    }

    // remove candidates from same col
    REP(r2,9) if (r2 != r) {
        removeBitIfExists(candidates[r2][c], value - 1);
    }

    // remove candidates from same region
    int startRow = r - r % 3;
    int startCol = c - c % 3;
    FOR(r2, startRow, startRow + 2) {
        FOR(c2, startCol, startCol + 2) {
            removeBitIfExists(candidates[r2][c2], value - 1);
        }
    }

    // Remove candidates for anti-king
    FOR(di,-1,1) FOR(dj,-1,1) {
        int r2 = r + di, c2 = c + dj;
        if (inside(r2, c2) && make_pair(r2, c2) != make_pair(r, c)) {
            removeBitIfExists(candidates[r2][c2], value - 1);
        }
    }

    // Remove candidates for anti-knight
    FOR(di,-2,2) FOR(dj,-2,2) if (di*di + dj*dj == 5) {
        int r2 = r + di, c2 = c + dj;
        if (inside(r2, c2) && make_pair(r2, c2) != make_pair(r, c)) {
            removeBitIfExists(candidates[r2][c2], value - 1);
        }
    }
}

void attempt() {
    // Find cell with minimum number of candidates.
    int bestRow = -1, bestCol = -1;
    REP(i,9) REP(j,9) {
        if (!board[i][j]) {
            if (bestRow < 0
                    || __builtin_popcount(candidates[i][j]) < __builtin_popcount(candidates[bestRow][bestCol])) {
                bestRow = i;
                bestCol = j;
            }
        }
    }
    if (bestRow < 0) {
        // No more unfilled cell --> we have found a solution.
        throw 1;
    }

    REP(value,9) {
        if (!CONTAIN(candidates[bestRow][bestCol], value)) continue;

        auto saveCandidates = candidates;
        auto saveBoard = board;
        setValue(bestRow, bestCol, value + 1);

        attempt();

        board = saveBoard;
        candidates = saveCandidates;
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cout << (fixed) << setprecision(9) << boolalpha;

    REP(i,9) REP(j,9) {
        candidates[i][j] = TWO(9) - 1;
    }

    vector<tuple<int, int, int>> fixeds;
    REP(i,9) REP(j,9) {
        int value = getChar() - '0';
        assert(0 <= value && value <= 9);
        if (value) {
            fixeds.emplace_back(i, j, value);
        }
    }

    if (fixeds.size() <= 1 || std::get<2> (fixeds[0]) != std::get<2> (fixeds[1])) {
        for (auto [i, j, value] : fixeds) {
            setValue(i, j, value);
        }
    } else {
        assert(fixeds.size() == 2);
        auto [r1, c1, val1] = fixeds[0];
        auto [r2, c2, val2] = fixeds[1];
        assert(val1 == val2);

        if (r1 == r2) {
            cout << "NO SOLUTION" << endl;
            return 0;
        }

        set<int> avail;
        FOR(x,1,9) avail.insert(x);
        avail.erase(val1);
        REP(j,9) {
            if (j != c1) {
                int val = *avail.begin();
                avail.erase(avail.begin());
                setValue(r1, j, val);
            } else {
                setValue(r1, c1, val1);
            }
        }
        if (!CONTAIN(candidates[r2][c2], val2 - 1)) {
            cout << "NO SOLUTION" << endl;
            return 0;
        }
        setValue(r2, c2, val2);
    }

    try {
        attempt();
        cout << "NO SOLUTION" << endl;
    } catch (...) {
        REP(i,9) {
            REP(j,9) {
                cout << board[i][j];
                // if (j % 3 == 2) cout << ' ';
            }
            cout << endl;
            // if (i % 3 == 2) cout << endl;
        }
    }

    return 0;
}
