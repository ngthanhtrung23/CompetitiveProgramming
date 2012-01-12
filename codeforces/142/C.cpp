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

int p3[22], M;
int f[10][300000], tu[10][300000], td[10][300000];
char board[20][20], cur = 'A';

int getBit(int x, int k) {
    return (x % p3[k+1]) / p3[k];
}

int setBit(int x, int k, int b) {
    return x - getBit(x, k) * p3[k] + b * p3[k];
}

int getprev(int state, int n) {
    int res = 0;
    REP(b,n) {
        int cur = getBit(state,b);
        cur--;
        if (cur < 0) cur = 0;
        res = setBit(res, b, cur);
    }
    return res;
}

int apply(int m, int c, int d, int state) {
    if (d == 1) {
        if (getBit(state,c) == 0 && getBit(state,c+1) == 0 && getBit(state,c+2) == 0) {
            state = setBit(state,c,1);
            state = setBit(state,c+1,3);
            state = setBit(state,c+2,1);
            return state;
        }
        else return -1;
    }
    if (d == 2) {
        if (getBit(state,c) <= 1 && getBit(state,c+1) <= 1 && getBit(state,c+2) == 0) {
            state = setBit(state,c,2);
            state = setBit(state,c+1,2);
            state = setBit(state,c+2,3);
            return state;
        }
        else return -1;
    }
    if (d == 3) {
        if (getBit(state,c) <= 2 && getBit(state,c+1) == 0 && getBit(state,c+2) <= 2) {
            state = setBit(state,c,3);
            state = setBit(state,c+1,3);
            state = setBit(state,c+2,3);
            return state;
        }
        else return -1;
    }
    if (d == 4) {
        if (getBit(state,c) == 0 && getBit(state,c+1) <= 1 && getBit(state,c+2) <= 1) {
            state = setBit(state,c,3);
            state = setBit(state,c+1,2);
            state = setBit(state,c+2,2);
            return state;
        }
        else return -1;
    }
}

int get(int m, int n, int state) {
    if (f[m][state] >= 0) return f[m][state];
    if (m >= M) return 0;
    int res = get(m+1, n, getprev(state,n));
    REP(c,n-2) FOR(d,1,4) {
        int news;
        news = apply(m, c, d, state);
        if (news != -1) {
            int cur = get(m, n, news) + 1;
            if (cur > res) {
                res = cur;
                tu[m][state] = c;
                td[m][state] = d;
            }
        }
    }
    return f[m][state] = res;
}

void trace(int m, int n, int state) {
    if (m >= M) return ;
    int c = tu[m][state];
    int d = td[m][state];
    if (d == 0) {
        trace(m+1,n,getprev(state,n));
        return ;
    }
    int news = apply(m, c, d, state);
    
    if (d == 1) {
        board[m-2][c] = board[m-2][c+1] = board[m-2][c+2] = board[m-1][c+1] = board[m][c+1] = cur;
    }
    if (d == 2) {
        board[m-2][c+2] = board[m-1][c] = board[m-1][c+1] = board[m-1][c+2] = board[m][c+2] = cur;
    }
    if (d == 3) {
        board[m-2][c+1] = board[m-1][c+1] = board[m][c] = board[m][c+1] = board[m][c+2] = cur;
    }
    if (d == 4) {
        board[m-2][c] = board[m-1][c] = board[m-1][c+1] = board[m-1][c+2] = board[m][c] = cur;
    }
    cur++;
    trace(m,n,news);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    p3[0] = 1; FOR(i,1,10) p3[i] = p3[i-1] * 4;
    int m, n;
    scanf("%d%d", &m, &n);
    {
        cur = 'A';
        M = m;
        memset(f, -1, sizeof f);
        memset(td, 0, sizeof td);
        printf("%d\n", get(2, n, 0));
        memset(board, '.', sizeof board);
        trace(2, n, 0);
        REP(i,m) {
            REP(j,n) cout << board[i][j];
            puts("");
        }
    }
    return 0;
}
