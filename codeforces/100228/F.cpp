#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

int X, Y, topWall, bottomWall, leftWall, rightWall;
pair<int,int> a[111];

int n;

bool collide(int i) {
    FOR(j,1,n) if (j != i)
        if (a[i] == a[j]) return true;
    return false;
}

bool canCompressX() {
    FOR(col,leftWall,rightWall-1) {
        int cnt = 0;
        FOR(i,1,n) if (a[i].second == col) ++cnt;

        if (cnt >= bottomWall - topWall) return false;
    }
    return true;
}

bool canCompressY() {
    FOR(row,topWall,bottomWall-1) {
        int cnt = 0;
        FOR(i,1,n) if (a[i].first == row) ++cnt;

        if (cnt >= rightWall - leftWall) return false;
    }
    return true;
}

void down(int d) {
    while (d--) {
        if (!canCompressX()) return ;

        ++topWall;
        FOR(i,1,n) if (a[i].first < topWall) {
            a[i].first = topWall;
            while (collide(i)) ++a[i].first;
        }
    }
}

void left(int d) {
    while (d--) {
        if (!canCompressY()) return ;

        --rightWall;

        FOR(i,1,n) if (a[i].second >= rightWall) {
            a[i].second = rightWall - 1;
            while (collide(i)) --a[i].second;
        }
    }
}

void up(int d) {
    while (d--) {
        if (!canCompressX()) return ;

        --bottomWall;
        FOR(i,1,n) if (a[i].first >= bottomWall) {
            a[i].first = bottomWall - 1;
            while (collide(i)) --a[i].first;
        }
    }
}

void right(int d) {
    while (d--) {
        if (!canCompressY()) return ;

        ++leftWall;

        FOR(i,1,n) if (a[i].second < leftWall) {
            a[i].second = leftWall;
            while (collide(i)) ++a[i].second;
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    while (cin >> X >> Y && (X || Y)) {
        cin >> n;

        FOR(i,1,n) cin >> a[i].first >> a[i].second;

        string dir;
        while (cin >> dir) {
            topWall = 0, bottomWall = X;
            leftWall = 0, rightWall = Y;
            if (dir == "done") break;
            int d; cin >> d;

            if (dir == "down") down(d);
            if (dir == "up") up(d);
            if (dir == "left") left(d);
            if (dir == "right") right(d);
        }
        sort(a+1, a+n+1);

        cout << "Data set " << ++test << " ends with boxes at locations";
        FOR(i,1,n) cout << " (" << a[i].first << ',' << a[i].second << ')';
        cout << '.' << endl;
    }
    return 0;
}
