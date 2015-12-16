
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

const int MN = 211;

int nRow, nCol, nBlack, nWhite;
pair<int,int> black[MN], white[MN];
int cy[MN], sy, cx[MN], sx;
int a[MN][MN];

void RR() {
    sy = 0;
    FOR(i,1,nBlack) cy[++sy] = black[i].second;
    FOR(i,1,nWhite) cy[++sy] = white[i].second;
    sort(cy+1, cy+sy+1);
    sy = unique(cy+1, cy+sy+1) - cy - 1;

    FOR(i,1,nBlack) black[i].second = lower_bound(cy+1, cy+sy+1, black[i].second) - cy;
    FOR(i,1,nWhite) white[i].second = lower_bound(cy+1, cy+sy+1, white[i].second) - cy;

    sx = 0;
    FOR(i,1,nBlack) cx[++sx] = black[i].first;
    FOR(i,1,nWhite) cx[++sx] = white[i].first;
    sort(cx+1, cx+sx+1);
    sx = unique(cx+1, cx+sx+1) - cx - 1;

    FOR(i,1,nBlack) black[i].first = lower_bound(cx+1, cx+sx+1, black[i].first) - cx;
    FOR(i,1,nWhite) white[i].first = lower_bound(cx+1, cx+sx+1, white[i].first) - cx;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> nRow >> nCol >> nBlack >> nWhite) {
        memset(a, 0, sizeof a);
        FOR(i,1,nBlack) {
            cin >> black[i].first >> black[i].second;
            black[i].first += 8;
            black[i].second += 5;
        }
        FOR(i,1,nWhite) {
            cin >> white[i].first >> white[i].second;
            white[i].first += 8;
            white[i].second += 5;
        }
        RR();
        FOR(i,1,nBlack) a[black[i].first][black[i].second]--;
        FOR(i,1,nWhite) a[white[i].first][white[i].second]++;

        FOR(i,1,sx) FOR(j,1,sy) {
            a[i][j] = a[i-1][j] + a[i][j-1] - a[i-1][j-1] + a[i][j];
        }

        if (nBlack == 0) {
            cout << 0 << endl;
            continue;
        }

        int res = nBlack + nWhite;

        FOR(x1,1,sx) FOR(x2,x1,sx) {
            if (cx[x1] < 1 || cx[x2] > nRow) continue;

            FOR(y1,1,sy) FOR(y2,y1,sy) {
                if (cy[y1] < 1 || cy[y2] > nCol) continue;

                res = min(res, nBlack +
                        a[x2][y2] - a[x1-1][y2] - a[x2][y1-1] + a[x1-1][y1-1]);
            }
        }
        cout << res << endl;
    }
}
