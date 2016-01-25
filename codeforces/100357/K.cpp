
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

char a[444][5011];
int mat[444];
char s[444];

struct Node {
    int rooti, rootj;
    int maxCol, maxRow;
};

Node go(int l, int r, int startRow, int startCol) {
    if (l == r) {
        a[startRow][startCol] = s[l];
        Node res;
        res.rooti = startRow;
        res.rootj = startCol;
        res.maxRow = startRow;
        res.maxCol = startCol;
        return res;
    }
    if (s[l] == '(' && mat[l] == r) {
        return go(l+1, r-1, startRow, startCol);
    }
    REP(turn,2) {
        int sum = 0;
        char need;
        FORD(x,r,l) {
            if (s[x] == ')') ++sum;
            else if (s[x] == '(') --sum;
            else if (sum == 0) {
                bool ok = false;
                if (turn == 0 && (s[x] == '+' || s[x] == '-')) ok = true;
                if (turn == 1 && (s[x] == '/' || s[x] == '*')) ok = true;
                if (turn == 2 && s[x] == '^') ok = true;
                if (!ok) continue;

                Node left = go(l, x-1, startRow + 2, startCol);
                Node res;
                res.rooti = startRow;
                res.rootj = left.maxCol + 3;
                Node right = go(x+1, r, startRow + 2, res.rootj + 3);

                res.maxCol = right.maxCol;
                res.maxRow = max(left.maxRow, right.maxRow);

                a[left.rooti - 1][left.rootj] = '|';
                a[right.rooti - 1][right.rootj] = '|';

                a[left.rooti - 2][left.rootj] = '.';
                a[right.rooti - 2][right.rootj] = '.';

                FOR(j,left.rootj + 1, right.rootj - 1)
                    a[res.rooti][j] = '-';
                a[res.rooti][res.rootj - 1] = '[';
                a[res.rooti][res.rootj] = s[x];
                a[res.rooti][res.rootj + 1] = ']';
                return res;
            }
        }
    }

    int sum = 0;
    char need;
    FOR(x,l,r) {
        if (s[x] == ')') ++sum;
        else if (s[x] == '(') --sum;
        else if (sum == 0 && s[x] == '^') {
            Node left = go(l, x-1, startRow + 2, startCol);
            Node res;
            res.rooti = startRow;
            res.rootj = left.maxCol + 3;
            Node right = go(x+1, r, startRow + 2, res.rootj + 3);

            res.maxCol = right.maxCol;
            res.maxRow = max(left.maxRow, right.maxRow);

            a[left.rooti - 1][left.rootj] = '|';
            a[right.rooti - 1][right.rootj] = '|';

            a[left.rooti - 2][left.rootj] = '.';
            a[right.rooti - 2][right.rootj] = '.';

            FOR(j,left.rootj + 1, right.rootj - 1)
                a[res.rooti][j] = '-';
            a[res.rooti][res.rootj - 1] = '[';
            a[res.rooti][res.rootj] = s[x];
            a[res.rooti][res.rootj + 1] = ']';
            return res;
        }
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);

    while (scanf("%s\n", &s[0]) == 1) {
        memset(a, ' ', sizeof a);
        int l = strlen(s);
        stack<int> st;
        memset(mat, -1, sizeof mat);
        REP(i,l) {
            if (s[i] == '(') st.push(i);
            else if (s[i] == ')') {
                int j = st.top(); st.pop();
                mat[i] = j;
                mat[j] = i;
            }
        }
        auto p = go(0, l - 1, 1, 1);

        FOR(i,1,p.maxRow) {
            FOR(j,1,p.maxCol) putchar(a[i][j]);
            puts("");
        }
        puts("");
    }
}
