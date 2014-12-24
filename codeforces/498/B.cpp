#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int t[5011], p[5011];
double f[2][5011], last[5011];
double power[111][5011], win[111][5011];

void init() {
    FOR(i,0,100) {
        double p = i / (double) 100.0;
        FOR(k,0,5000)
            power[i][k] = pow(p, k);

        win[i][1] = p;
        FOR(k,2,5000)
            win[i][k] = (1 - win[i][k-1]) * p + win[i][k-1];
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    init();
    int n, sumT;
    while (cin >> n >> sumT) {
        memset(f, 0, sizeof f);
        FOR(i,1,n) {
            cin >> p[i] >> t[i];
            last[i] = 1.0;
            FOR(done,1,t[i]-1) {
                last[i] -= power[p[i]][1] * power[100-p[i]][done-1];
            }
        }
        f[0][0] = 1.0;
        double res = 0.0;
        int rot = 0;
        FOR(i,1,n) {
            memset(f[1-rot], 0, sizeof f[1-rot]);
            if (t[i] == 1) {
                FOR(T,1,sumT) {
                    f[1-rot][T] = f[rot][T-1];
                }
            }
            else {
                double cur_sum = 0.0;
                FOR(T,1,sumT) {
                    if (T-1 >= t[i]) {
                        cur_sum -= last[i] * f[rot][T-1-t[i]];
                    }
                    if (T-1 >= t[i]-1) {
                        cur_sum -= power[p[i]][1] * power[100-p[i]][t[i]-2] * f[rot][T-t[i]];
                    }
                    cur_sum *= power[100-p[i]][1];

                    if (T >= t[i]) cur_sum += last[i] * f[rot][T-t[i]];
                    cur_sum += power[p[i]][1] * f[rot][T-1];

                    f[1-rot][T] = cur_sum;
                }
            }
            rot = 1 - rot;

//            PR(f[rot], sumT);
            FOR(T,1,sumT) {
                if (T == sumT) res += f[rot][T] * i;
                else if (i == n) res += f[rot][T] * n;
                else {
                    if (T + t[i+1] > sumT) {
                        res += f[rot][T] * (1 - win[p[i+1]][sumT - T]) * i;
                    }
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}
