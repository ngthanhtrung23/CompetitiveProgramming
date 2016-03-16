
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;
const int MOD = 1e9 + 7;

struct Hash {
    int x, y;
    
    Hash() : x(0), y(0) {}
    Hash(int x, int y) : x(x), y(y) {}

    Hash operator + (const Hash& a) const {
        return Hash(x + a.x, (y + a.y) % MOD);
    }
    Hash operator - (const Hash& a) const {
        return Hash(x - a.x, (y - a.y + MOD) % MOD);
    }
    Hash operator * (const Hash& a) const {
        return Hash(x * a.x, y * a.y % MOD);
    }
    Hash extend(char c) {
        return Hash(x * 311 + c, (y * 311 + c) % MOD);
    }

    friend ostream& operator << (ostream& cout, Hash& h) {
        cout << '(' << h.x << ' ' << h.y << ')';
        return cout;
    }
};

bool operator < (const Hash& a, const Hash& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}

map<string,int> siteId;
pair<vector<Hash>,int> sitePaths[MN];
string siteName[MN];
int nPath, nSite;

void init() {
    nSite = 0;
    siteId.clear();
    REP(i,MN) sitePaths[i].first.clear();
}

char tmp[100111];

pair<string,string> splitPath(string s) {
    int slash = 0, third = 0;
    REP(i,SZ(s)) {
        char c = s[i];
        if (c != '/') continue;

        ++slash;
        if (slash == 3) third = i;
    }
    if (slash < 3) {
        return make_pair(s, "");
    }
    return make_pair(s.substr(0, third), s.substr(third));
}

int getId(string s) {
    if (siteId.count(s)) return siteId[s];

    int x = SZ(siteId) + 1;
    siteName[x] = s;
    siteId[s] = x;
    return x;
}

Hash getHash(string s) {
    Hash res;
    for(char c : s) res = res.extend(c);
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%lld\n", &nPath) == 1) {
        init();
        FOR(i,1,nPath) {
            scanf("%s\n", &tmp[0]);
            string s(tmp);
            auto t = splitPath(s);

            int id = getId(t.first);
            sitePaths[id].first.push_back(getHash(t.second));
        }
        int nSite = SZ(siteId);
        FOR(i,1,nSite) {
            sort(sitePaths[i].first.begin(), sitePaths[i].first.end());
            sitePaths[i].second = i;

            sitePaths[i].first.resize(
                    unique(sitePaths[i].first.begin(), sitePaths[i].first.end()) - sitePaths[i].first.begin());
        }
        sort(sitePaths+1, sitePaths+nSite+1);

//        FOR(i,1,nSite) {
//            PR0(sitePaths[i].first, SZ(sitePaths[i].first));
//        }

        int i = 1, cnt = 0;
        while (i <= nSite) {
            int j = i;
            while (j < nSite && sitePaths[j+1].first == sitePaths[j].first) ++j;

            if (j > i) ++cnt;
            i = j + 1;
        }
        cout << cnt << endl;
        i = 1;
        while (i <= nSite) {
            int j = i;
            while (j < nSite && sitePaths[j+1].first == sitePaths[j].first) ++j;

            if (j > i) {
                FOR(x,i,j) printf("%s ", siteName[sitePaths[x].second].c_str());
                puts("");
            }
            i = j + 1;
        }
    }
}
