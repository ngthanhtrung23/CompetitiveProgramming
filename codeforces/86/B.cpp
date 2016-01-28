
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

const int MN = 1011;
int m, n;
char a[MN][MN];

const int di[12] = {-1,1,0,0,-1,-1,1,1,-2,2,0,0};
const int dj[12] = {0,0,-1,1,-1,1,-1,1,0,0,-2,2};

bool used[11];

void adj(int i, int j, int val) {
	REP(dir,12) {
		int ii = i + di[dir], jj = j + dj[dir];
		if (a[ii][jj] >= '0' && a[ii][jj] <= '9') {
			used[a[ii][jj] - '0'] = val;
        }
	}
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
	while (scanf("%d%d\n", &m, &n) == 2) {
		memset(a, '#', sizeof a);
		FOR(i,1,m) scanf("%s\n", &a[i][1]);

		FOR(i,1,m) FOR(j,1,n-1) if (a[i][j] == '.' && a[i][j+1] == '.') {
			adj(i, j, 1);
			adj(i, j+1, 1);

			int cur = 0;
			while (used[cur]) ++cur;
            
			adj(i, j, 0);
			adj(i, j+1, 0);

			a[i][j] = a[i][j+1] = (char) (cur + '0');
		}

        FOR(i,1,m-1) FOR(j,1,n) if (a[i][j] == '.' && a[i+1][j] == '.') {
            adj(i, j, 1);
            adj(i+1, j, 1);

            int cur = 0;
            while (used[cur]) ++cur;

            adj(i, j, 0);
            adj(i+1, j, 0);

            a[i][j] = a[i+1][j] = (char) (cur + '0');
        }

        try {
            FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.') {
                REP(dir,4) {
                    int ii = i + di[dir], jj = j + dj[dir];
                    if (a[ii][jj] >= '0' && a[ii][jj] <= '9') {
                        a[i][j] = a[ii][jj];
                        break;
                    }
                }
                if (a[i][j] == '.') throw 1;
            }

            FOR(i,1,m) {
                FOR(j,1,n) putchar(a[i][j]);
                puts("");
            }
        } catch (int e) {
            puts("-1");
        }
        puts("");
	}
}
