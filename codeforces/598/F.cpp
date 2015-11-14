#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <sstream>
using namespace std;
#pragma comment(linker, "/STACK:255000000")

typedef long long ll;

#define rep(i, a, b) for(i = (a); i < (b); ++i)
#define repb(i, a, b) for(i = (a) - 1; i >= (b); --i)
#define repd(i, a, b, d) for(i = (a); i < (b); i += (d))
#define repbd(i, a, b, d) for(i = (a) - 1; i >= (b); i -= (d))
#define reps(i, s) for(i = 0; (s)[i]; ++i)
#define repl(i, l) for(i = l.begin(); i != l.end(); ++i)

#define in(f, a) scanf("%"#f, &(a))

bool firstout = 1;

#define out(f, a) printf("%"#f, (a))
#define outf(f, a) printf((firstout) ? "%"#f : " %"#f, (a)), firstout = 0
#define nl printf("\n"), firstout = 1

#define all(x) (x).begin(),(x).end()
#define sqr(x) ((x) * (x))
#define mp make_pair

template<class T>
T &minn(T &a, T b)
{
    if(b < a) a = b;
    return a;
}

template<class T>
T &maxx(T &a, T b)
{
    if(a < b) a = b;
    return a;
}

#define inf 1012345678
#define eps 1e-9


#ifdef XDEBUG
#define mod 23
#else
#define mod 1000000007
#endif

int &madd(int &a, int b)
{
    a += b;
    if(a >= mod) a -= mod;
    return a;
}

int &msub(int &a, int b)
{
    a -= b;
    if(a < 0) a += mod;
    return a;
}

int &mmult(int &a, int b)
{
    return a = (ll)a * b % mod;
}

int mdiv(ll a, ll b, ll m)
{
    a = (a % m + m) % m;
    b = (b % m + m) % m;
    if(a % b == 0) return a / b;
    return (a + m * mdiv(-a, m, b)) / b;
}

#define N 1012
#define M 1012

int n, m, q, na, nr;
double X[2 * N], Y[2 * N];
pair<double, double> A[2 * N];
pair<pair<double, double>, int> R[2 * N];

int main()
{
#ifdef XDEBUG
    freopen("in.txt", "rt", stdin);
#else
#endif

    int i, j, k;
    char c;
    int a, d;

    int ts;
#if 0
    int tss;
	in(d, tss);
	rep(ts, 1, tss + 1)
#else
    for(ts = 1; in(d, n) > 0; ++ts)
#endif
    {
        in(d, q);
        rep(i, 0, n) in(lf, X[i]), in(lf, Y[i]);
        rep (i, n, n + n) X[i] = X[i - n], Y[i] = Y[i - n];
        for(; q--;) {
            na = nr = 0;
            double x, y, xx, yy, a, b, c;
            in(lf, x); in(lf, y); in(lf, xx); in(lf, yy);
            a = yy - y;
            b = x - xx;
            c = +y * xx - x * yy;
            rep (i, 0, n) {
                double p1 = a * X[i] + b * Y[i] + c;
                double p2 = a * X[i + 1] + b * Y[i + 1] + c;
                if (p1 * p2 < 0 && fabs(p1) > eps && fabs(p2) > eps) {
                    x = X[i + 1] - X[i];
                    y = Y[i + 1] - Y[i];
                    p1 = fabs(p1);
                    p2 = fabs(p2);
                    p1 /= p1 + p2;
                    A[na++] = mp(X[i] + p1 * x, Y[i] + p1 * y);
                }
                if (fabs(p1) < eps && fabs(p2) < eps) {
                    pair<double, double> r1, r2;
                    r1 = mp(X[i], Y[i]);
                    r2 = mp(X[i + 1], Y[i + 1]);
                    if (r2 < r1) swap(r1, r2);
                    R[nr++] = mp(r1, 1);
                    R[nr++] = mp(r2, -1);
                }
            }
            rep (i, 1, n + 1) {
                if (fabs(a * X[i - 1] + b * Y[i - 1] + c) > eps && fabs(a * X[i] + b * Y[i] + c) <= eps) {
                    double p1 = a * X[i - 1] + b * Y[i - 1] + c;
                    for (j = i + 1; fabs(a * X[j] + b * Y[j] + c) <= eps; ++j);
                    double p2 = a * X[j] + b * Y[j] + c;
                    if (p1 * p2 < 0 && fabs(p1) > eps && fabs(p2) > eps) {
                        A[na++] = mp(X[i], Y[i]);
                    }
                }
            }
            sort(A, A + na);
            //out(d, na); nl;
            repd(i, 0, na, 2) {
                //utf(.2lf, A[i].first); outf(.2lf, A[i].second); nl;
                //outf(.2lf, A[i + 1].first); outf(.2lf, A[i + 1].second); nl;
                R[nr++] = mp(A[i], 1);
                R[nr++] = mp(A[i + 1], -1);
            }
            sort(R, R + nr);
            double res = 0.;
            int r = 0;
            rep (i, 0, nr) {
                //outf(.2lf, R[i].first.first); outf(.2lf, R[i].first.second); outf(d, R[i].second); nl;
                if (r > 0) res += hypot(R[i].first.first - R[i - 1].first.first, R[i].first.second - R[i - 1].first.second);
                r += R[i].second;
            }
            out(.7lf, res); nl;
        }
    }

    return 0;
}