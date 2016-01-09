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

char turn;

pair<int,int> idToPos[66];
int posToId[11][11];
int board[11][11];

void init() {
    int nid = 0;
    FOR(i,1,8) FOR(j,1,8) {
        if ((i + j) % 2) {
            posToId[i][j] = ++nid;
            idToPos[nid] = make_pair(i, j);
        }
    }
//    DEBUG(nid);
}

bool validCaptureDirection(pair<int,int> p, int di, int dj, int side) {
    if (abs(di) != 2) return false;
    if (abs(dj) != 2) return false;
    if (abs(board[p.first][p.second]) == 1) { // NOT KING
        if (di * side < 0) return false;
    }
    return true;
}

bool outside(pair<int,int> p) {
    return p.first < 1 || p.first > 8 || p.second < 1 || p.second > 8;
}

bool canCapture(pair<int,int> p, pair<int,int> mid, pair<int,int> target,
        int di, int dj, int side) {
    if (outside(mid) || outside(target)) return false;

    // direction must be good
    if (!validCaptureDirection(p, di, dj, side)) return false;

    // middle position must be enemy's piece
    if (board[mid.first][mid.second] * side >= 0) return false;

    // target must be empty
    if (board[target.first][target.second]) return false;

    return true;
}

bool canCaptureAnything(int side, pair<int,int> p) {
    for(int di = -2; di <= 2; di += 4)
        for(int dj = -2; dj <= 2; dj += 4) {
            auto mid = make_pair(p.first + di/2, p.second + dj/2);
            auto target = make_pair(p.first + di, p.second + dj);

            if (outside(mid) || outside(target)) continue;

            if (canCapture(p, mid, target, di, dj, side)) {
                return true;
            }
        }
    return false;
}

bool canCaptureAnything(int side) {
    FOR(i,1,8) FOR(j,1,8) if (board[i][j] * side > 0) {
        auto p = make_pair(i, j);
        if (canCaptureAnything(side, p)) return true;
    }
    return false;
}

bool canNormal(pair<int,int> p, pair<int,int> to,
        int di, int dj, int side) {
    if (outside(to)) return false;
    if (canCaptureAnything(side, p)) return false;

    if (abs(board[p.first][p.second]) == 1) { // NOT KING
        if (side * di < 0) return false;
    }
    if (board[to.first][to.second]) return false;

    return true;
}

bool valid(int side, string s) {
    REP(i,SZ(s)-1) if (s[i] == '-' && s[i+1] == '-') return false;
    REP(i,SZ(s)) {
        if (s[i] >= '0' && s[i] <= '9') continue;
        if (s[i] == '-') s[i] = ' ';
        else return false;
    }

    istringstream ss(s);
    vector<int> id;
    int u;
    while (ss >> u) id.push_back(u);
//    PR0(id, SZ(id));

    REP(i,SZ(id)) if (id[i] < 1 || id[i] > 32) return false;

    if (SZ(id) <= 1) return false;

    // check if this position is indeed of this side
    auto p = idToPos[id[0]];
    if (side * board[p.first][p.second] <= 0) return false;

    // middle moves are all capture moves
    FOR(i,1,SZ(id)-1) {
        auto to = idToPos[id[i]];
        
        // check this move
        int di = to.first - p.first;
        int dj = to.second - p.second;

        if (abs(di) == 1 && abs(dj) == 1) {
            if (i < SZ(id)-1) return false;
            if (i == 1 && canCaptureAnything(side)) return false;

//            DEBUG(i);

            if (!canNormal(p, to, di, dj, side)) return false;
            swap(board[p.first][p.second], board[to.first][to.second]);

            p = to;
        }
        else {
            auto mid = make_pair(p.first + di / 2, p.second + dj / 2);
            if (!canCapture(p, mid, to, di, dj, side)) return false;

            // make the move
            int tmp = board[p.first][p.second];
            board[p.first][p.second] = 0;
            board[mid.first][mid.second] = 0;
            board[to.first][to.second] = tmp;
            p = to;
        }

        if ((side == 1 && p.first == 8)
                || (side == -1 && p.first == 1)) {
            if (abs(board[p.first][p.second]) == 2) continue;

            board[p.first][p.second] *= 2;
            if (i == SZ(id) - 1) return true;
            else {
                return false;
            }
        }

        if (abs(di) == 1) return true;
    }
    if (canCaptureAnything(side, p)) {
        return false;
    }
    return true;
}

void printBoard() {
    FOR(i,1,8) {
        FOR(j,1,8) cout << setw(3) << board[i][j] << ' ';
        cout << endl;
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    init();
    int nRed, nWhite;
    while (cin >> nRed >> nWhite && nRed && nWhite) {
        memset(board, 0, sizeof board);
        FOR(i,1,nRed) {
            int u; cin >> u;
            bool isKing = u < 0;
            u = abs(u);
            auto p = idToPos[u];
//            DEBUG(u);
            assert(board[p.first][p.second] == 0);

            board[p.first][p.second] = (isKing) ? 2 : 1;
        }
        FOR(i,1,nWhite) {
            int u; cin >> u;
            bool isKing = u < 0;
            u = abs(u);

            auto p = idToPos[u];
            assert(board[p.first][p.second] == 0);

            board[p.first][p.second] = (isKing) ? -2 : -1;
        }
//        cout << "-----------" << endl;
//        printBoard();
        int nMove; cin >> nMove;
        char turn; cin >> turn;
        int side = (turn == 'R') ? 1 : -1;

        int invalid = -1;
        FOR(move,1,nMove) {
            string s; cin >> s;
            if (!valid(side, s)) {
                if (invalid < 0) {
                    invalid = move;
                }
            }
            side = -side;

//            DEBUG(move);
//            printBoard();
        }
        if (invalid < 0) cout << "All moves valid\n";
        else cout << "Move " << invalid << " is invalid\n";
    }
}
