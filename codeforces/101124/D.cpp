
#include <bits/stdc++.h>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) \
  { cout << #X << " = " << (X) << endl; }
#define PR(A, n)                      \
  {                                   \
    cout << #A << " = ";              \
    FOR(_, 1, n) cout << A[_] << ' '; \
    cout << endl;                     \
  }
#define PR0(A, n)                  \
  {                                \
    cout << #A << " = ";           \
    REP(_, n) cout << A[_] << ' '; \
    cout << endl;                  \
  }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

typedef pair<int, int> P;

P toPos(string s) {
  int row = s[0] - 'a' + 1;
  int col = s[1] - '0';
  return make_pair(row, col);
}

P king, knight, bishop, opp;
char board[11][11];

void printBoard() {
  FOR(i, 1, 8) {
    FOR(j, 1, 8) {
      if (i == opp.first && j == opp.second)
        cout << 'O';
      else if (board[i][j] == ' ')
        cout << '.';
      else
        cout << board[i][j];
    }
    cout << endl;
  }
}

bool inside(int u, int v) { return u >= 1 && u <= 8 && v >= 1 && v <= 8; }

bool empty(int u, int v) { return inside(u, v) && board[u][v] == ' '; }

set<P> canAttackKing(P king) {
  set<P> res;
  FOR(di, -1, 1) FOR(dj, -1, 1) if (di || dj) {
    int u = king.first + di;
    int v = king.second + dj;

    if (inside(u, v)) {
      res.insert(make_pair(u, v));
    }
  }
  return res;
}

set<P> canMoveKing(P king) {
  set<P> res;
  auto all = canAttackKing(king);
  for (auto m : all) {
    if (empty(m.first, m.second)) res.insert(m);
  }
  return res;
}

set<P> canAttackKnight(P knight) {
  set<P> res;
  FOR(di, -2, 2) FOR(dj, -2, 2) if (di * di + dj * dj == 5) {
    int u = knight.first + di;
    int v = knight.second + dj;

    if (inside(u, v)) {
      res.insert(make_pair(u, v));
    }
  }
  return res;
}

set<P> canMoveKnight(P knight) {
  set<P> res;
  auto all = canAttackKnight(knight);
  for (auto m : all) {
    if (empty(m.first, m.second)) res.insert(m);
  }
  return res;
}

set<P> canAttackBishop(P bishop) {
  set<P> res;
  for (int di = -1; di <= 1; di += 2)
    for (int dj = -1; dj <= 1; dj += 2) {
      int u = bishop.first, v = bishop.second;
      while (true) {
        u += di;
        v += dj;
        if (!inside(u, v)) break;

        res.insert(make_pair(u, v));
        if (!empty(u, v)) break;
      }
    }
  return res;
}

set<P> canMoveBishop(P bishop) {
  set<P> res;
  auto all = canAttackBishop(bishop);
  for (auto m : all) {
    if (empty(m.first, m.second)) res.insert(m);
  }
  return res;
}

void print(P m) { cout << (char)(m.first - 1 + 'a') << m.second; }

bool isAttacked(P opp) {
  set<P> a = canAttackKnight(knight);
  set<P> b = canAttackBishop(bishop);

  if (a.find(opp) != a.end()) return true;
  if (b.find(opp) != b.end()) return true;

  return false;
}

bool canMove(P opp, bool debug = false) {
  set<P> a = canAttackKnight(knight);
  set<P> b = canAttackBishop(bishop);
  set<P> c = canAttackKing(king);

  FOR(di, -1, 1) FOR(dj, -1, 1) if (di || dj) {
    auto m = make_pair(opp.first + di, opp.second + dj);

    if (inside(m.first, m.second)) {
      if (a.find(m) == a.end() && b.find(m) == b.end() &&
          c.find(m) == c.end()) {
        return true;
      }
    }
  }
  return false;
}

bool checkKing() {
  auto moves = canMoveKing(king);
  for (auto m : moves) {
    // make the move!
    swap(board[king.first][king.second], board[m.first][m.second]);
    auto saveKing = king;
    king = m;

    // check if under attacked
    if (isAttacked(opp) && !canMove(opp)) {
      cout << 'K';
      print(m);
      cout << endl;
      return true;
    }

    // restore board
    king = saveKing;
    swap(board[king.first][king.second], board[m.first][m.second]);
  }
  return false;
}

bool checkKnight() {
  auto moves = canMoveKnight(knight);
  for (auto m : moves) {
    // make the move!
    swap(board[knight.first][knight.second], board[m.first][m.second]);
    auto saveKnight = knight;
    knight = m;

    // check if under attacked
    if (isAttacked(opp) && !canMove(opp)) {
      cout << 'N';
      print(m);
      cout << endl;
      return true;
    }

    // restore board
    knight = saveKnight;
    swap(board[knight.first][knight.second], board[m.first][m.second]);
  }
  return false;
}

bool checkBishop() {
  auto moves = canMoveBishop(bishop);
  for (auto m : moves) {
    // make the move!
    swap(board[bishop.first][bishop.second], board[m.first][m.second]);
    auto saveBishop = bishop;
    bishop = m;

    // check if checkmate
    if (isAttacked(opp) && !canMove(opp)) {
      cout << 'B';
      print(m);
      cout << endl;
      return true;
    }

    // restore board
    bishop = saveBishop;
    swap(board[bishop.first][bishop.second], board[m.first][m.second]);
  }
  return false;
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  string a, b, c, d;
  while (cin >> a >> b >> c >> d) {
    king = toPos(a);
    bishop = toPos(b);
    knight = toPos(c);
    opp = toPos(d);

    memset(board, ' ', sizeof board);
    board[king.first][king.second] = 'K';
    board[bishop.first][bishop.second] = 'B';
    board[knight.first][knight.second] = 'N';

    if (checkKing()) continue;
    if (checkKnight()) continue;
    if (checkBishop()) continue;
    cout << "impossible" << endl;
  }
}
