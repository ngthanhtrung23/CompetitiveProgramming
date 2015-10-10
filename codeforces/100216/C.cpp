
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

#define MAXM 100 // leave one extra 
#define MAXN 100 // leave one extra 
#define EPS 1e-9 
#define INF 1.0/0.0 
double A[MAXM][MAXN]; 
int basis[MAXM], out[MAXN]; 
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
double simplex(int m, int n, double C[][MAXN], double X[]) { 
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
      if (A[ii][jj] >= -EPS) return -INF; 
      pivot(m,n,ii,jj); 
   } 
   for(;;) { 
      for (j=jj=0;j<n;j++) 
         if (A[0][j]<A[0][jj] || (A[0][j]==A[0][jj] && out[j]<out[jj])) 
            jj=j; 
      if (A[0][jj] > -EPS) break; 
      for (i=1,ii=0;i<=m;i++) 
         if ((A[i][jj]>EPS) && 
               (!ii || (A[i][n]/A[i][jj] < A[ii][n]/A[ii][jj]-EPS) || 
            ((A[i][n]/A[i][jj] < A[ii][n]/A[ii][jj]+EPS) && (basis[i] < basis[ii])))) 
         ii=i; 
      if (A[ii][jj] <= EPS) return INF; 
      pivot(m,n,ii,jj); 
   } 
   for (j=0;j<n;j++)
      X[j] = 0; 
   for (i=1;i<=m;i++) 
      if (basis[i] >= 0) 
         X[basis[i]] = A[i][n]; 
   return A[0][n]; 
} 

int n;
double a[11][11];

int main() {
    ios :: sync_with_stdio(false);
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);

    while (cin >> n) {
        REP(i,n) REP(j,n) cin >> a[i][j];
        double res = -1e100;

        double X[11], saveX[11];
        REP(j,n) {
            int nVar = n;
            int nEqu = 0;
            // row 0 : objective function
            memset(A, 0, sizeof A);
            REP(i,n)
                A[0][i] = a[i][j];

            // constraint: sum = 1
            ++nEqu;
            REP(i,n)
                A[nEqu][i] = 1;
            A[nEqu][n] = 1;

            ++nEqu;
            REP(i,n)
                A[nEqu][i] = -1;
            A[nEqu][n] = -1;

            // constraints: less then other columns
            REP(jj,n) if (jj != j) {
                ++nEqu;
                REP(i,n)
                    A[nEqu][i] = a[i][j] - a[i][jj];
                A[nEqu][n] = 0;
            }

//            DEBUG(j);
//            REP(i,nEqu+1) PR0(A[i], nVar+1);
            double cur = simplex(nEqu, nVar, A, X);

            if (cur > res) {
                res = cur;
                REP(i,n) saveX[i] = X[i];
            }

//            DEBUG(cur);
//            PR0(X, nVar);
        }

        cout << (fixed) << setprecision(12) << res << endl;
        REP(i,n) cout << saveX[i] << ' '; cout << endl;
    }
}
