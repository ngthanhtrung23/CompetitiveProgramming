
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 211;

bool empty(const string& s) {
    for(char c : s) if (c == 'X') return false;
    return true;
}
int nPieces, width, boxHeight;

struct Piece {
    string a[MN];
    int height;

    void normalize() {
        while (height > 0 && empty(a[1])) {
            FOR(i,1,height-1) a[i] = a[i+1];
            --height;
        }
    }

    void read() {
        cin >> height;
        FORD(i,height,1) cin >> a[i];
        normalize();
    }

    bool hasOverlap(const Piece& piece, int on) {
        for(int i = 1; i <= piece.height && on <= height; ++i, ++on) {
            REP(j,width)
                if (piece.a[i][j] == 'X' && a[on][j] == 'X') return true;
        }
        return false;
    }

    void putPiece(const Piece& piece) {
        if (piece.height == 0) return ;

        int on = height+1;
        while (on > 1 && !hasOverlap(piece, on-1)) --on;
        
        for(int i = 1, u = on; i <= piece.height; ++i, ++on) {
            if (on > boxHeight) continue;
            REP(j,width)
                if (piece.a[i][j] == 'X') {
                    a[on][j] = 'X';
                }
        }

        height = max(height, on-1);
    }

    void print() const {
        FORD(i,height,1) {
            cout << a[i] << endl;
        }
    }
} cur_board, pieces[MN];

Piece createEmptyBoard() {
    Piece res;
    res.height = 0;

    string emptyRow = "";
    REP(turn,width) emptyRow += '.';

    FOR(i,1,boxHeight) res.a[i] = emptyRow;
    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    while (cin >> nPieces >> width >> boxHeight && nPieces) {
        FOR(i,1,nPieces) {
            pieces[i].read();
        }
        vector<int> res;
        res.push_back(0);

        cur_board = createEmptyBoard();

        FOR(i,1,nPieces) {
            cur_board.putPiece(pieces[i]);
            if (cur_board.height > boxHeight) {
                cur_board = createEmptyBoard();
                res.push_back(0);
                cur_board.putPiece(pieces[i]);
            }
            res.back() = cur_board.height;
        }

        if (res.back() == 0) res.pop_back();
        REP(i,SZ(res)) {
            if (i > 0) cout << ' ';
            cout << res[i];
        }
        cout << endl;
    }
}

