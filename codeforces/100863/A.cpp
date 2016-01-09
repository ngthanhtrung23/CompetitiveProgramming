
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int isLeap(int y) {
    if (y % 400 == 0) return 1;
    if (y % 100 == 0) return 0;
    if (y % 4 == 0) return 1;
    return 0;
}

struct Date {
    int y, m, d;
    Date() {}
    Date(int y, int m, int d) : y(y), m(m), d(d) {}

    int getNDays(int y, int m) {
        if (m == 1 || m == 3 || m == 5 || m == 7
                || m == 8 || m == 10 || m == 12) return 31;
        if (m == 2) return 28 + isLeap(y);
        return 30;
    }

    int exists() {
        if (d > getNDays(y, m)) return false;
        return 1;
    }

    void print() {
        cout << setw(2) << setfill('0') << d << '.'
             << setw(2) << setfill('0') << m << '.'
             << y << endl;
    }
};

Date add(Date cur, int y, int m) {
    y += m / 12;
    m %= 12;

    Date res = cur;
    res.y += y;
    res.m += m;

    if (res.m > 12) {
        res.y += 1;
        res.m %= 12;
    }

    if (!res.exists()) {
        res.m++;
        res.d = 1;
    }
    return res;
}

bool operator < (const Date& a, const Date& b) {
    if (a.y != b.y) return a.y < b.y;
    if (a.m != b.m) return a.m < b.m;
    if (a.d != b.d) return a.d < b.d;
    return false;
}
bool operator == (const Date& a, const Date& b) {
    return a.y == b.y
        && a.m == b.m
        && a.d == b.d;
}
bool operator <= (const Date& a, const Date& b) {
    return a < b || a == b;
}

pair<Date, pair<int,int> > age[100111];
int mInc, nGap, kTimes;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d%d%d", &mInc, &nGap, &kTimes) == 3) {
        Date birth;
        scanf("%d.%d.%d", &birth.d, &birth.m, &birth.y);

//        cout << "birth = "; birth.print();

        age[0] = make_pair(Date(1, 1, 1), make_pair(60, 0));

        Date up(2012, 1, 1);

        FOR(i,1,kTimes) {
            age[i] = make_pair(up, make_pair(60, i * mInc));
            up = add(up, 0, nGap);
        }
        age[kTimes+1] = make_pair(Date(99999,1,1), make_pair(60, kTimes*mInc));
        
        for(int addm = 0; ; addm += mInc) {
            Date cur = add(birth, 60, addm);

//            cout << "Attempt retire after 60y + " << addm << "m" << endl;
//            cout << "Current date: ";
//            cur.print();

            int i = 0;
            while (age[i+1].first <= cur) ++i;

//            cout << "Latest rule at: "; age[i].first.print();

            if (age[i].second.second <= addm) {
                cur.print();
                break;
            }
        }
    }
}
