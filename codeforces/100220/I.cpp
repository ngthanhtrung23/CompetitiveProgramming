
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

string s, tmp;

int x[1011][1011];
char a[3011][3011];
int nCell;

int getNum(const string& s, int i) {
    int from = i + 1;
    while (s[from] != '"') ++from;
    int to = from + 1;
    while (s[to] != '"') ++to;

    int res = 0;
    FOR(x,from+1,to-1)
        res = res * 10 + s[x] - '0';
    return res;
}

void parseCell(int row, string s) {
    ++nCell;
    int nRow = 1, nCol = 1;

    REP(i,SZ(s))
        if (s[i] == 'c') {
            nCol = getNum(s, i);
        }
        else if (s[i] == 'r') {
            nRow = getNum(s, i);
        }
        else if (s[i] == '>') break;

    int startCol = 1;
    while (x[row][startCol]) ++startCol;
    FOR(i,row,row+nRow-1)
        FOR(j,startCol,startCol+nCol-1) {
            if (x[i][j]) throw 1;
            x[i][j] = nCell;
        }

    int i1 = row * 2 - 1;
    int i2 = (row + nRow - 1) * 2 + 1;

    int j1 = startCol * 2 - 1;
    int j2 = (startCol + nCol - 1) * 2 + 1;

    FOR(j,j1,j2) {
        if (a[i1][j] == ' ') a[i1][j] = '-';
        if (a[i2][j] == ' ') a[i2][j] = '-';
    }
    FOR(i,i1,i2) {
        if (a[i][j1] == ' ') a[i][j1] = '|';
        if (a[i][j2] == ' ') a[i][j2] = '|';
    }

    a[i1][j1] = a[i1][j2] = a[i2][j1] = a[i2][j2] = '+';
//    cout << i1 << ' ' << j1 << ' ' << i2 << ' ' << j2 << endl;
}

void parseRow(int row, string s) {
    int start = -1;
    REP(i,SZ(s)-4) {
        if (s.substr(i, 3) == "<td") {
            start = i;
        }
        else if (s.substr(i, 5) == "</td>") {
            parseCell(row, s.substr(start, i - start));
        }
    }
}

void parseTable(string s) {
    int row = 0;

    int start = -1;
    REP(i,SZ(s)-4) {
        if (s.substr(i, 3) == "<tr") {
            start = i;
        }
        else if (s.substr(i, 5) == "</tr>") {
            ++row;
            parseRow(row, s.substr(start, i - start));
        }
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("table.in", "r", stdin);
    freopen("table.out", "w", stdout);
    while (getline(cin, tmp)) {
        REP(i,SZ(tmp))
            if (tmp[i] >= 'A' && tmp[i] <= 'Z') {
                tmp[i] ^= ' ';
            }
        s += tmp;
    }

    memset(a, ' ', sizeof a);
    try {
        parseTable(s);
    } catch (int e) {
        cout << "ERROR" << endl;
        return 0;
    }

    int nRow = 0;
    FOR(i,1,3000) FOR(j,1,3000) {
        if (a[i][j] != ' ') nRow = i;
    }
    FOR(i,1,nRow) {
        int nCol = 0;
        FOR(j,1,3000) if (a[i][j] != ' ') nCol = j;

        FOR(j,1,nCol) cout << a[i][j];
        cout << endl;
    }
}
