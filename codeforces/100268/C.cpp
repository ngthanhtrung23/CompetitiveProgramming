#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
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

#define EPS 1e-9 
double A[55][55]; 
int basis[55], out[55]; 
void pivot(int m, int n, int a, int b) { 
   int i,j; 
   for (i=0;i<=m;i++) 
      if (i!=a) 
         for (j=0;j<=n;j++)
            if (j!=b) 
               A[i][j] -= A[a][j] * A[i][b] / A[a][b]; 
   for (j=0;j<=n;j++) 
      if (j!=b) A[a][j] /= A[a][b]; 
   for (i=0;i<=m;i++) 
      if (i!=a) A[i][b] = -A[i][b]/A[a][b]; 
         A[a][b] = 1/A[a][b]; 
   swap(basis[a], out[b]);
} 
bool simplex(int m, int n, double C[][5], double X[]) { 
   int i,j,ii,jj; // i,ii are row indexes; j,jj are column indexes 
   for (i=1;i<=m;i++) 
      for (j=0;j<=n;j++) 
         A[i][j] = C[i][j]; 
   for (j=0;j<=n;j++) A[0][j] = -C[0][j]; 
   for (i=0;i<=m;i++) basis[i] = -i; 
   for (j=0;j<=n;j++) out[j] = j; 
   for(;;) { 
      for (i=ii=1;i<=m;i++) 
         if (A[i][n]<A[ii][n] || (A[i][n]==A[ii][n] && basis[i]<basis[ii])) 
            ii=i; 
      if (A[ii][n] >= -EPS) break; 
      for (j=jj=0;j<n;j++) 
         if (A[ii][j]<A[ii][jj]-EPS || (A[ii][j]<A[ii][jj]-EPS && out[i]<out[j])) 
            jj=j;
      if (A[ii][jj] >= -EPS) return false;
      pivot(m,n,ii,jj); 
   } 
   return true;
}

// m - number of (less than) inequalities, n - number of variables 
// C - (m+1) by (n+1) array of coefficients: 
// row 0 - objective function coefficients 
// row 1:m - less-than inequalities 
// column 0:n-1 - inequality coefficients 
// column n - inequality constants (0 for objective function) 
// X[n] - result variables 
// return value - maximum value of objective function 
// (-inf for infeasible, inf for unbounded) 

int n;
int R[55], T[55], S[55];
double C[55][5], X[5];

bool check(int i) {
    REP(var,3) REP(turn,2) REP(dx,2) REP(dy,2) REP(dz,2) {
        memset(C, 0, sizeof C);
        int nEqu = 0, nVar = 3;

        C[0][0] = C[0][1] = C[0][2] = 1;

        ++nEqu;
        C[nEqu][var] = (turn) ? 1 : -1; C[nEqu][3] = -1;

        FOR(j,1,n) if (j != i) {
            ++nEqu;
            C[nEqu][0] = (dx) ? -R[i] + R[j] : R[i] - R[j];
            C[nEqu][1] = (dy) ? -T[i] + T[j] : T[i] - T[j];
            C[nEqu][2] = (dz) ? -S[i] + S[j] : S[i] - S[j];
            C[nEqu][3] = 0;
        }
        // if (R[i] == 0 && T[i] == 0 && S[i] == 0 && !dx && !dy && !dz) {
        //     REP(i,nEqu+1) {
        //         PR0(C[i], 4);
        //     }
        // }
        if (simplex(nEqu, nVar, C, X)) return true;
    }
    return false;
}

int main() {
    // ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        FOR(i,1,n) cin >> R[i] >> T[i] >> S[i];

        // PR(R, n);
        // PR(T, n);
        // PR(S, n);

        FOR(i,1,n) {
            if (check(i)) putchar('T');
            else putchar('F');
        }
        puts("");
    }
    return 0;
}
