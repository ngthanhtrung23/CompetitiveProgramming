#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < (n); ++i)
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)

int test;
double p;
double f[25], C[25][25];
double mu[25], mm[25];

void solve(){
    cin >> p;
    REP(i, 25) REP(j, 25) C[i][j] = 0;
    for(int i = 0; i < 25; i++) C[0][i] = 1;
    FOR(i, 1, 24) FOR(j, 1, i) C[j][i] = C[j - 1][i - 1] + C[j][i - 1];
    mu[0] = 1; mm[0] = 1;
    FOR(i, 1, 24) {
        mu[i] = mu[i - 1] * p;
        mm[i] = mm[i - 1] * (1 - p);
    }

    f[0] = 0;

    for(int i = 1; i <= 20; i ++){
        double A = 0, P = 0;
        for(int j = 1; j <= i; j++){
            double X = C[j][i] * mu[j] * mm[i - j];
            P += X;
            A += X * f[i - j];
        }
        f[i] = (A + 1) / P;
//        cout << i << " " << A << " " << P << " " <<f[i] << endl;
    }
    cout << fixed << setprecision(5) << f[20] << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);

    cin >> test;
    FOR(itest, 1, test){
        cout << "Case #" << itest << ": ";
        solve();
    }

    return 0;
}
