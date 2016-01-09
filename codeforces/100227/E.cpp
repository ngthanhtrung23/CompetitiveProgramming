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

bool outside(pair<int,int> p) {
    return p.first < 1 || p.first > 8 || p.second < 1 || p.second > 8;
}

void printBoard() {
    FOR(i,1,8) {
        FOR(j,1,8) cout << setw(3) << board[i][j] << ' ';
        cout << endl;
    }
}

bool isKing(pair<int,int> p) {
    return abs(board[p.first][p.second]) == 2;
}

int side(pair<int,int> p) {
    int t = board[p.first][p.second];
    if (t < 0) return -1;
    if (t > 0) return 1;
    return 0;
}

int validDirection(pair<int,int> p, int di, int dj) {
    if (abs(di) != abs(dj)) return false;
    if (abs(di) < 1 || abs(di) > 2) return false;

    if (isKing(p)) return true;

    if (side(p) * di <= 0) return false;
    return true;
}

bool canMove(pair<int,int> p, pair<int,int> to) {
    if (outside(to)) return false;

    int di = to.first - p.first;
    int dj = to.second - p.second;

    if (!validDirection(p, di, dj)) return false;
    if (abs(di) == 2) return false;

    if (side(to) != 0) return false;

    return true;
}

bool canJump(pair<int,int> p, pair<int,int> to) {
    int di = to.first - p.first;
    int dj = to.second - p.second;
    pair<int,int> mid = make_pair(p.first + di/2, p.second + dj/2);

    if (outside(to) || outside(mid)) return false;

    if (!validDirection(p, di, dj)) return false;
    if (abs(di) == 1) return false;

    if (side(to) != 0) return false;
    if (side(mid) != -side(p)) return false;

    return true;
}

bool canJump(pair<int,int> p) {
    for(int di=-2; di <= 2; di += 4) 
        for(int dj=-2; dj <= 2; dj += 4) {
            auto to = make_pair(p.first + di, p.second + dj);
            if (canJump(p, to)) return true;
        }
    return false;
}

bool canJump(int turn) {
    FOR(i,1,8) FOR(j,1,8) {
        auto p = make_pair(i, j);
        if (side(p) == turn && canJump(p)) return true;
    }
    return false;
}

bool promote(pair<int,int> p) {
    if ((board[p.first][p.second] == 1 && p.first == 8)
            || (board[p.first][p.second] == -1 && p.first == 1)) {
        board[p.first][p.second] *= 2;
        return true;
    }
    return false;
}

void makeMove(pair<int,int> &p, pair<int,int> to) {
    swap(board[p.first][p.second], board[to.first][to.second]);
    p = to;
}

void makeJump(pair<int,int>&p, pair<int,int> to) {
    int di = to.first - p.first;
    int dj = to.second - p.second;
    pair<int,int> mid = make_pair(p.first + di/2, p.second + dj/2);

    swap(board[p.first][p.second], board[to.first][to.second]);
    board[mid.first][mid.second] = 0;

    p = to;
}

bool valid(int turn, string s) {
    REP(i,SZ(s)-1) if (s[i] == '-' && s[i+1] == '-') return false;
    REP(i,SZ(s)) {
        if (s[i] == '-') s[i] = ' ';
        else if (s[i] < '0' || s[i] > '9') return false;
    }
    istringstream ss(s);
    vector<int> ids;
    int u; while (ss >> u) ids.push_back(u);

//    PR0(ids, SZ(ids));
    auto p = idToPos[ids[0]];
    if (side(p) != turn) return false;

    FOR(i,1,SZ(ids)-1) {
        auto to = idToPos[ids[i]];
        if (canMove(p, to)) {
//            cout << "MOVE" << endl;
            if (i == 1 && canJump(side(p))) return false;
            if (canJump(p)) return false;
            makeMove(p, to);

            if (promote(p)) return i == SZ(ids) - 1;

            if (i != SZ(ids)-1) return false;
            else return true;
        }
        else if (canJump(p, to)) {
//            cout << "JUMP" << endl;
            makeJump(p, to);
            if (promote(p)) return i == SZ(ids) - 1;
        }
        else return false;
    }
    if (canJump(p)) return false;
    return true;
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
