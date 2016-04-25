#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
#define double long double
using namespace std;

const int MN = 100111;

int n;
double Max[MN], Min[MN], SMax[MN], SMin[MN];

pair<double,double> get(double s, double p) {
    double a = 1.0;
    double b = -s;
    double c = p;

    double delta = fabs(b*b - 4*a*c);

    return make_pair(
            (-b - sqrt(delta)) / 2 / a,
            (-b + sqrt(delta)) / 2 / a
            );
}

double SA[MN], SB[MN], A[MN], B[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%d", &n) == 1) {
#undef double
        FOR(i,1,n) { double t; scanf("%lf", &t); Max[i] = t; }
        FOR(i,1,n) { double t; scanf("%lf", &t); Min[i] = t; }
#define double long double

        FOR(i,1,n) SMax[i] = SMax[i-1] + Max[i];
        SMin[n+1] = 0;
        FORD(i,n,1) SMin[i] = SMin[i+1] + Min[i];

        FORD(i,n-1,0) {
            double L = 1.0 - SMax[i];
            double S = L + SMin[i+1];
            double P = SMin[i+1];

            auto t = get(S, P);
            SA[i+1] = t.first;
            SB[i+1] = t.second;
        }
        SA[n+1] = SB[n+1] = 0.0;

        FORD(i,n,1) {
            A[i] = SA[i] - SA[i+1];
            B[i] = SB[i] - SB[i+1];
        }
#undef double
        FOR(i,1,n) printf("%.9f ", (double) A[i]); puts("");
        FOR(i,1,n) printf("%.9f ", (double) B[i]); puts("");
    }
}
