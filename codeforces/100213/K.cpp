
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

int nSection, startSection;
pair<int,int> pool;

int c[111][111]; // common edge between 2 section
double totalRate;

struct Section {
public:
    int x1, y1, x2, y2, d;
    int common_boundary;
    bool finished;
    double expected_finish;
    double rate;

private:
    int volume;

    double filled;

public:
    void read() {
        cin >> x1 >> y1 >> x2 >> y2 >> d;
        d *= 10;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        rate = 0;
        filled = 0;
        common_boundary = 0;
        finished = false;
        expected_finish = 1e20;

        volume = (x2 - x1) * (y2 - y1) * d;
    }

    void set_rate(double r) {
        assert(!finished);

        if (r > 1e-9) {
            rate = r;
            double each = rate / (x2 - x1) / (y2 - y1);
            expected_finish = (d - filled) / each;
        }
    }

    void fill(double time) {
        // 1s --> rate
        double each = rate / (x2 - x1) / (y2 - y1);
        filled += each * time;
    }
} a[111];

int common(int u, int v, int x, int y) {
    if (y < u || v < x) return 0;
    return min(v, y) - max(u, x);
}

void initBoundary() {
    FOR(i,1,nSection) {
        FOR(j,1,nSection) if (i != j) {
            if (a[i].x2 == a[j].x1 || a[j].x2 == a[i].x1)
                c[i][j] += common(a[i].y1, a[i].y2, a[j].y1, a[j].y2);

            if (a[i].y2 == a[j].y1 || a[j].y2 == a[i].y1)
                c[i][j] += common(a[i].x1, a[i].x2, a[j].x1, a[j].x2);
        }

        if (a[i].x1 == 0)
            c[i][0] += common(0, pool.second, a[i].y1, a[i].y2);
        if (a[i].x2 == pool.first)
            c[i][0] += common(0, pool.second, a[i].y1, a[i].y2);

        if (a[i].y1 == 0)
            c[i][0] += common(0, pool.first, a[i].x1, a[i].x2);

        if (a[i].y2 == pool.second)
            c[i][0] += common(0, pool.first, a[i].x1, a[i].x2);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("swimming.in", "r", stdin);
    freopen("swimming.out", "w", stdout);

    while (cin >> nSection >> pool.first >> pool.second >> startSection >> totalRate) {
        FOR(i,1,nSection) a[i].read();

        initBoundary();

//        FOR(i,1,nSection) {
//            PR(c[i], nSection);
//        }

        ll sum_boundary = 0;
        a[startSection].set_rate(totalRate);

        double ellapsed_time = 0.0;
        FOR(turn,1,nSection) {
            int u = -1;
            
            FOR(i,1,nSection) if (!a[i].finished) {
                if (u < 0 || a[i].expected_finish < a[u].expected_finish)
                    u = i;
            }

            double t = a[u].expected_finish;
            a[u].finished = true;

//            DEBUG(t);
//            cout << u << " is filled" << endl;

            FOR(i,1,nSection) if (!a[i].finished) {
                a[i].fill(t);
            }

            FOR(v,0,nSection) {
                if (!a[v].finished) {
                    a[v].common_boundary += c[u][v];
                    sum_boundary += c[u][v];
                }
                else {
                    sum_boundary -= c[u][v];
                }
            }

//            DEBUG(sum_boundary);

            FOR(v,1,nSection) if (!a[v].finished) {
                a[v].set_rate(totalRate / sum_boundary * a[v].common_boundary);
            }

            ellapsed_time += t;

//            FOR(i,1,nSection) if (!a[i].finished) {
//                cout << i << ' ' << a[i].rate << ' ' << a[i].expected_finish << endl;
//            }
        }
        cout << (fixed) << setprecision(12) << ellapsed_time << endl;
    }
}
