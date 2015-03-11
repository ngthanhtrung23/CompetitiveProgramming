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

const int daysInMonth[] = {
0, 31, 29, 31, 30, 31, 30,
   31, 31, 30, 31, 30, 31
};

int dayIndex(int month, int day) {
    int res = 0;
    FOR(i,1,month-1) res += daysInMonth[i];
    return res + day;
}

int secondId(int month, int day, int hour, int min, int sec) {
    return dayIndex(month, day) * 24 * 3600 + hour * 3600 + min * 60 + sec;
}

char tmp[11000111];
tuple<int,int,int,int,int> a[500111];
int x[5000111];

int main() {
    int n, M;
    while (scanf("%d%d\n", &n, &M) == 2) {
        int month, day, h, m, s;
        
        int k = 0;
        while (scanf("2012-%02d-%02d %02d:%02d:%02d", &month, &day, &h, &m, &s) == 5) {
            gets(tmp);
            int id = secondId(month, day, h, m, s);

            ++k;
            a[k] = make_tuple(month, day, h, m, s);
            x[k] = id;
        }
        
        bool ok = false;
        FOR(i,M,k) {
            int fr = x[i - M + 1], to = x[i];
            if (to - fr < n) {
                ok = true;
                auto res = a[i];
                printf("2012-%02d-%02d %02d:%02d:%02d\n",
                    get<0>(res),
                    get<1>(res),
                    get<2>(res),
                    get<3>(res),
                    get<4>(res));
                break;
            }
        }
        if (!ok) cout << -1 << endl;
    }
    return 0;
}

