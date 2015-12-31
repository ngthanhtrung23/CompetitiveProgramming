
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

typedef vector< vector<int> > State;

vector< State > f[211];
bool has[211];

void print(State cur) {
    for(auto p : cur) {
        PR0(p, SZ(p));
    }
}

State getNext(int n, State cur) {
    memset(has, 0, sizeof has);

    FORD(i,SZ(cur)-1,0) {
        auto p = cur[i];

        if (i == SZ(cur) - 1) {
            if (SZ(p) > 2) {
//                DEBUG(i);
                State next = cur;
                auto last = next.back();
                next.pop_back();

                int x = last[SZ(last) - 2];
                int y = last.back();
                last.pop_back();
                last.pop_back();
                last.push_back(y);
                
                next.push_back(last);
                next.push_back({x});
//                cout << "next = " << endl;
//                print(next);
                return next;
            }
        }
        else {
            // if can increase p
            FORD(j,SZ(p)-1,0) {
                // insert after position j
                int bound = (j == SZ(p) - 1) ? p[j] : p[j+1];
                FOR(val,bound+1,n) {
                    if (has[val]) {
//                        DEBUG(i);
//                        DEBUG(j);
//                        PR0(p, SZ(p));

                        State next;
                        REP(ii,i) next.push_back(cur[ii]);

                        vector<int> add;
                        REP(jj,SZ(p))
                            if (jj <= j) add.push_back(p[jj]);
                            else has[p[jj]] = true;

                        add.push_back(val);
                        has[val] = 0;
//                        PR0(add, SZ(add));

                        next.push_back(add);

                        FOR(x,1,n) if (has[x]) {
                            next.push_back({x});
                        }
//                        cout << "next = " << endl;
//                        print(next);
                        return next;
                    }
                }

                has[p[j]] = true;
            }
        }
        for(int x : p) has[x] = true;
    }
    State next;
    FOR(i,1,n) next.push_back({i});
    return next;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("partitions.in", "r", stdin);
    freopen("partitions.out", "w", stdout);
    int n, k;
    while (cin >> n >> k && n && k) {
        State cur;
        string tmp;
        getline(cin, tmp);
        FOR(i,1,k) {
            getline(cin, tmp);
            stringstream ss(tmp);

            vector<int> p;
            int x;
            while (ss >> x) p.push_back(x);

            cur.push_back(p);
        }
//        cout << "-----" << endl;
//        print(cur);
//        cout << "-----" << endl;

        State next = getNext(n, cur);
//        print (next);

        cout << n << ' ' << SZ(next) << '\n';
        for(auto p : next) {
            for(int x : p) cout << x << ' ';
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
    FOR(i,1,7) {
        DEBUG(i);
        if (i == 1) {
            f[1].push_back({{1}});
        } else {
            for(auto p : f[i-1]) {
                auto cur = p;
                // add new vector {i}
                auto next = cur;
                next.push_back({i});
                f[i].push_back(next);

                REP(j,SZ(cur)) {
                    auto next = cur;
                    next[j].push_back(i);

                    f[i].push_back(next);
                }
            }
        }
        sort(f[i].begin(), f[i].end());
        f[i].resize(unique(f[i].begin(), f[i].end()) - f[i].begin());

        DEBUG(SZ(f[i]));
        DEBUG(i);

        REP(j,SZ(f[i])) {
            cout << "--------------------" << endl;
            int jj = (j + 1) % SZ(f[i]);

            print(f[i][j]);
            cout << "--> " << endl;
            print(f[i][jj]);

            assert(getNext(i, f[i][j]) == f[i][jj]);
            cout << endl;
        }
        cout << endl;
    }
}
