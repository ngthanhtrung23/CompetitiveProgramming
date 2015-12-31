#include <bits/stdc++.h>

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

int encode[1600111], decode[50111], nCode, match[50111][13];
ll f[2][50111];

char a[111][111];
int m, n, p3[20], tmp[20], st[20];

void gen(int i, int p3, int sum, int code) {
    if (i == n+2) {
        if (sum) return ;
        decode[nCode] = code;
        encode[code] = nCode;
        
        int top = 0;
        FOR(i,1,n+1)
            if (tmp[i] == 1) {
                top++; st[top] = i;
            }
            else if (tmp[i] == -1) {
                match[nCode][i] = st[top];
                match[nCode][st[top]] = i;
                top--;
            }
            
        nCode++;
        return ;
    }
    FOR(now,-1,1)
    if (sum + now >= 0) {
        tmp[i] = now;
        int next = code;
        if (now == 1) next += p3;
        else if (now == -1) next += p3 + p3;
        gen(i+1, p3*3, sum + now, next);
    }
}

#define e(x) encode[x]

int main() {
    freopen("pipe.in", "r", stdin);
    freopen("pipe.out", "w", stdout);
    cin >> m >> n;
    if (m < n) swap(m, n);

    int mm = 0, nn = 0;
    memset(a, '*', sizeof a);
    FOR(i,1,m) FOR(j,1,n) a[i][j] = '.';
    mm = m;
    nn = n;
    
    gen(1,1,0,0);
    
    f[0][0] = 1;
    int now = 0;
    
    p3[0] = 1; FOR(i,1,14) p3[i] = p3[i-1] * 3;
    
    FOR(i,1,m) {
        FOR(j,0,n-1) { // (i,j) --> (i,j+1)
            memset(f[1-now], 0, sizeof f[1-now]);
            int cur, next, x, y;
            REP(mask,nCode)
            if (f[now][mask]) {
//                cout << i << ' ' << j << ' ' << decode[mask] << ' ' << f[now][mask] << endl;
                cur = decode[mask];
                x = (cur % p3[j+1]) / p3[j];
                y = (cur % p3[j+2]) / p3[j+1];
                
                if (a[i][j+1] == '*') { // Can not add anything
                    if (x || y) continue;
                    else f[1-now][mask] += f[now][mask]; // Add nothing
                    continue;
                }
                if (!x && !y) {
                    if (a[i][j+2] == '.' && a[i+1][j+1] == '.')
                        f[1-now][e(cur + p3[j] + p3[j+1] + p3[j+1])] += f[now][mask]; // 00 --> 12
                }
                else if (!x && y == 1) {
                    if (a[i][j+2] == '.')
                        f[1-now][mask] += f[now][mask]; // 01 -> 01
                    if (a[i+1][j+1] == '.')
                        f[1-now][e(cur-p3[j+1]+p3[j])] += f[now][mask]; // 01 -> 10
                }
                else if (!x && y == 2) {
                    if (a[i][j+2] == '.')
                        f[1-now][mask] += f[now][mask]; // 02 -> 02
                    if (a[i+1][j+1] == '.')
                        f[1-now][e(cur-p3[j+1]-p3[j])] += f[now][mask]; // 02 -> 20
                }
                else if (x == 1 && !y) {
                    if (a[i+1][j+1] == '.')
                        f[1-now][mask] += f[now][mask]; // 10 -> 10
                    if (a[i][j+2] == '.')
                        f[1-now][e(cur-p3[j]+p3[j+1])] += f[now][mask]; // 10 -> 01
                }
                else if (x == 2 && !y) {
                    if (a[i+1][j+1] == '.')
                        f[1-now][mask] += f[now][mask]; // 20 -> 20
                    if (a[i][j+2] == '.')
                        f[1-now][e(cur+p3[j]+p3[j+1])] += f[now][mask]; // 20 -> 02
                }
                else if (x == 1 && y == 1) {
                    int jj = match[mask][j+2];
                    next = cur - p3[j] - p3[j+1] - p3[jj-1];
                    f[1-now][e(next)] += f[now][mask];
                }
                else if (x == 2 && y == 2) {
                    int jj = match[mask][j+1];
                    next = cur + p3[j] - p3[j+2] + p3[jj-1];
                    f[1-now][e(next)] += f[now][mask];
                }
                else if (x == 2 && y == 1) {
                    f[1-now][e(cur - p3[j] - p3[j] - p3[j+1])] += f[now][mask];
                }
                else if (x == 1 && y == 2) {
                    if (i == mm && j+1 == nn)
                        f[1-now][e(cur - p3[j] - p3[j+1] - p3[j+1])] += f[now][mask];
                }
            } // for mask
            
            now = 1 - now;
        } // for j
        
        // (i,n) --> (i+1,0)
        if (i < m) {
            memset(f[1-now], 0, sizeof f[1-now]);
            REP(mask,nCode)
            if (f[now][mask]) {
                int cur = decode[mask];
                int next = cur % p3[n+1];
                next = next * 3;
                f[1-now][e(next)] = f[now][mask];
            }
            now = 1 - now;
        }
    } // for i
    
    printf("%lld\n", f[now][0]);
    return 0;
}
