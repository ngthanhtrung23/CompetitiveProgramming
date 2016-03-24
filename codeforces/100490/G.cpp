#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 111;
int board[MN][MN], need[MN][MN];

struct Rect {
    int top, left, bottom, right;
    void read() {
        cin >> top >> left >> bottom >> right;
    }
} a[MN];
int n, nRow, nCol;
vector< pair<int,int> > res;

void print() {
    cout << "Panel container = new Panel(new GridBagLayout());" << endl;
    cout << "GridBagConstraints gbc = new GridBagConstraints();" << endl;
    for(auto p : res) {
        cout << "gbc.gridwidth = ";
        if (p.second < 0) cout << "GridBagConstraints.REMAINDER;\n";
        else cout << p.second << ";\n";
        cout << "gbc.gridheight = " << p.first << ";\n";
        cout << "container.add(new Component(), gbc);\n";
    }
}

pair<int,int> find() {
    REP(i,nRow) REP(j,nCol)
        if (board[i][j] == 0) 
            return make_pair(i, j);
    return make_pair(-1, -1);
}

bool emptyRow(int r) {
    REP(j,nCol) if (board[r][j]) return false;
    return true;
}
bool emptyCol(int c) {
    REP(r,nRow) if (board[r][c]) return false;
    return true;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("gridbaglayout.in", "r", stdin);
    freopen("gridbaglayout.out", "w", stdout);
    while (cin >> nRow >> nCol >> n) {
        memset(board, 0, sizeof board);
        memset(need, 0, sizeof need);

        try {
            res.clear();
            FOR(i,1,n) {
                a[i].read();
                FOR(u,a[i].top,a[i].bottom)
                    FOR(v,a[i].left,a[i].right) {
                        if (need[u][v]) throw 1;
                        need[u][v] = i;
                    }
            }

            int isFirst = true;
            int curRow = 0;
            int calcRow = 1, calcCol = 0;
            FOR(turn,1,n) {
                // we paint the board one component at a time
                // first, find the what is the top-left cell of this component
                pair<int,int> cur;
                if (isFirst) {
                    // if it is first of its row
                    cur = find();
                    curRow = cur.first;
                    ++calcRow;
                } else {
                    // if it is not first
                    cur.first = curRow;
                    cur.second = 0;
                    while (board[cur.first][cur.second]) ++cur.second;
                }

                // then we try to find the component that starts at this cell
                int comp = -1;
                FOR(i,1,n) if (a[i].top == cur.first && a[i].left == cur.second) {
                    comp = i;
                }
                if (comp < 0) throw 1;

                // now we set the size of the new component to this comp, and paint our board
                int height = a[comp].bottom - a[comp].top + 1;
                if (turn == n) {
                    if (calcCol < nCol || a[comp].right < nCol - 1) {
                        res.push_back(make_pair(
                                    height,
                                    a[comp].right - a[comp].left + 1));
                        isFirst = false;
                        calcCol = max(calcCol, a[comp].right + 1);
                    }
                    else {
                        res.push_back(make_pair(height, -1));
                        isFirst = true;
                        calcCol = max(calcCol, a[comp].right + 1);
                    }
                }
                else if (a[comp].right == nCol - 1) {
                    res.push_back(make_pair(height, -1));
                    isFirst = true;
                    calcCol = max(calcCol, a[comp].left + 1);
                }
                else {
                    res.push_back(make_pair(
                                height,
                                a[comp].right - a[comp].left + 1));
                    isFirst = false;
                    calcCol = max(calcCol, a[comp].right + 1);
                }

                FOR(u,a[comp].top,a[comp].bottom)
                    FOR(v,a[comp].left,a[comp].right)
                        board[u][v] = comp;
            }

            REP(i,nRow) REP(j,nCol) if (need[i][j] != board[i][j]) throw 1;
            int can = 0;
            REP(i,nRow) if (board[i][nCol-1]) can = 1;
            if (!can) throw 1;

            can = 0;
            REP(i,nCol) if (board[nRow-1][i]) can = 1;
            if (!can) throw 1;

            if (calcCol != nCol) throw 1;

            print();
            cout << endl;
        } catch (...) {
            cout << "Impossible" << endl;
            cout << endl;
        }
    }
}
