#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>
#include <sstream>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);

int m, n, cnt[1011][1011];
char a[1011][1011];
bool mark[300];
const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

int now;
pair<int,int> x[100];

bool inside(int i, int j) {
    if (i < 0 || j < 0) return false;
    if (i > m || j > n) return false;
    return true;
}

char getColor() {
    FOR(cur,'0','9') mark[cur] = false;
    
    FOR(p,1,now) {
        REP(dir,4) {
            int i = x[p].F + di[dir];
            int j = x[p].S + dj[dir];
            if (a[i][j] >= '0' && a[i][j] <= '9') mark[a[i][j]] = true;
        }
    }
    
    char c = '0';
    while (mark[c]) c++;
    return c;
}

bool check(char c) {
    c = getColor();
    
    FOR(p,1,now) if (a[x[p].F][x[p].S] != '.') return false;
    
    bool ok = true;
    FOR(p,1,now) a[x[p].F][x[p].S] = c;
    FOR(p,1,now) {
        int i = x[p].F, j = x[p].S;
        REP(dir,4) {
            int ii = i + di[dir], jj = j + dj[dir];
            if (a[ii][jj] == '.') {
                cnt[ii][jj]--;
                if (!cnt[ii][jj]) ok = false;
            }
        }
    }
    
    if (!ok) { // Roll back
        FOR(p,1,now) {
            int i = x[p].F, j = x[p].S;
            REP(dir,4) {
                int ii = i + di[dir], jj = j + dj[dir];
                if (a[ii][jj] == '.') {
                    cnt[ii][jj]++;
                    if (!cnt[ii][jj]) ok = false;
                }
            }
        }
        FOR(p,1,now) a[x[p].F][x[p].S] = '.';
    }
    return ok;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> m >> n;
    FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
    
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.') {
        cnt[i][j] = 0;
        REP(dir,4) {
            int ii = i + di[dir], jj = j + dj[dir];
            if (inside(ii,jj) && a[ii][jj] == '.') cnt[i][j]++;
        }
        if (!cnt[i][j]) {
            puts("-1");
            return 0;
        }
    }
    else cnt[i][j] = -1;
    
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.') {
//        FOR(u,1,m) {
//            FOR(v,1,n) cout << a[u][v]; cout << endl;
//        }
        
        char c;
        // xx
        now = 2; x[1] = MP(i,j); x[2] = MP(i,j+1);
        if (check(c)) continue;
        now = 2; x[1] = MP(i,j); x[2] = MP(i+1,j);
        if (check(c)) continue;
        
        // xxx
        now = 3; x[1] = MP(i,j); x[2] = MP(i,j+1); x[3] = MP(i,j+2);
        if (check(c)) continue;
        now = 3; x[1] = MP(i,j); x[2] = MP(i+1,j); x[3] = MP(i+2,j);
        if (check(c)) continue;
        
        // 3
        now = 3; x[1] = MP(i,j); x[2] = MP(i,j+1); x[3] = MP(i+1,j);
        if (check(c)) continue;
        now = 3; x[1] = MP(i,j); x[2] = MP(i,j+1); x[3] = MP(i+1,j+1);
        if (check(c)) continue;
        now = 3; x[1] = MP(i,j); x[2] = MP(i+1,j); x[3] = MP(i+1,j+1);
        if (check(c)) continue;
        now = 3; x[1] = MP(i,j); x[2] = MP(i+1,j-1); x[3] = MP(i+1,j);
        if (check(c)) continue;
        
        // 4
        now = 4;
        x[1] = MP(i,j); x[2] = MP(i,j+1); x[3] = MP(i,j+2); x[4] = MP(i+1,j+1);
        if (check(c)) continue;
        x[1] = MP(i,j); x[2] = MP(i+1,j-1); x[3] = MP(i+1,j); x[4] = MP(i+2,j);
        if (check(c)) continue;
        x[1] = MP(i,j); x[2] = MP(i+1,j); x[3] = MP(i+1,j+1); x[4] = MP(i+2,j);
        if (check(c)) continue;
        x[1] = MP(i,j); x[2] = MP(i+1,j-1); x[3] = MP(i+1,j); x[4] = MP(i+1,j+1);
        if (check(c)) continue;
        
        // 5
        now = 5;
        x[1] = MP(i,j); x[2] = MP(i+1,j-1); x[3] = MP(i+1,j); x[4] = MP(i+1,j+1); x[5] = MP(i+2,j);
        if (check(c)) continue;
        
        puts("-1");
        return 0;
    }
    
    FOR(i,1,m) {
        FOR(j,1,n) cout << a[i][j];
        puts("");
    }
    return 0;
}
