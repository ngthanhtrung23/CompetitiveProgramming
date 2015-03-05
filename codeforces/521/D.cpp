
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
using namespace std;

const int MN = 100111;

pair<int,int> change[MN];
vector<pair<int,int> > add[MN];
vector<pair<int,int> > mult[MN];
int nSkill, nUpgrade, nChoose, a[MN];

vector< pair<int,int> > res;

struct Fraction {
    ll x, y;
    Fraction(ll _x=0, ll _y=1) {
        ll g = __gcd(_x, _y);
        x = _x / g;
        y = _y / g;
    }
};

bool operator < (const Fraction& a, const Fraction& b) {
    // a.x/a.y < b.x/b.y
    ll ia = a.x / a.y;
    ll ib = b.x / b.y;
    if (ia != ib) return ia > ib;
    else {
        ll axx = a.x % a.y;
        ll bxx = b.x % b.y;

        // axx / a.y < bxx / b.y
        return axx * b.y > bxx * a.y;
    }
}

int main() {
    while (scanf("%d%d%d", &nSkill, &nUpgrade, &nChoose) == 3) {
        FOR(i,1,nSkill) {
            scanf("%d", &a[i]);
            change[i] = make_pair(0, 0);
            add[i].clear();
            mult[i].clear();
        }
        FOR(i,1,nUpgrade) {
            int typ, applyOn, value;
            scanf("%d%d%d", &typ, &applyOn, &value);
            if (typ == 1) {
                change[applyOn] = max(change[applyOn], make_pair(value, i));
            }
            else if (typ == 2) {
                add[applyOn].push_back(make_pair(value, i));
            }
            else if (typ == 3) {
                mult[applyOn].push_back(make_pair(value, i));
            }
        }
        FOR(i,1,nSkill) {
            sort(add[i].begin(), add[i].end());
            reverse(add[i].begin(), add[i].end());
        }

        set< pair<Fraction, pair<int, int> > > s;

        // Change
        FOR(i,1,nSkill) if (change[i].first > a[i]) {
            s.insert(make_pair(
                        Fraction(change[i].first - a[i], a[i]),
                        make_pair(1, change[i].second)));
        }
        // Add
        FOR(i,1,nSkill) {
            ll tu = a[i], mau = a[i];
            for(auto x : add[i]) {
                tu += x.first;

                s.insert(make_pair(
                            Fraction(tu, mau),
                            make_pair(2, x.second)));

                mau += x.first;
            }
        }
        // Mult
        FOR(i,1,nSkill) {
            for(auto x : mult[i]) {
                s.insert(make_pair(
                            Fraction(x.first, 1),
                            make_pair(3, x.second)));
            }
        }

        REP(turn,nChoose) {
            if (s.empty()) break;
            auto x = *s.begin();
            s.erase(s.begin());

            res.push_back(x.second);
        }

        sort(res.begin(), res.end());
        printf("%d\n", res.size());
        for(auto x : res) printf("%d ", x.second); puts("");
    }
    return 0;
}

