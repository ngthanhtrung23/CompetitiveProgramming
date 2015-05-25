
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

bool canUse[211];
struct Block {
    int first, last, id;
} blocks[111];
bool operator < (const Block& a, const Block& b) {
    return a.first < b.first;
}
int nBlock, q, avail;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> q >> avail) {
        memset(canUse, false, sizeof canUse);
        FOR(i,1,avail) canUse[i] = true;

        nBlock = 0;
        int lastId = 0;
        while (q--) {
            string typ; cin >> typ;
            if (typ == "alloc") {
                int u; cin >> u;
                int id = -1;
                FOR(i,1,avail-u+1) {
                    bool allCanUse = true;
                    FOR(j,i,i+u-1) allCanUse = allCanUse && canUse[j];
                    if (allCanUse) {
                        ++nBlock;
                        id = ++lastId;
                        blocks[nBlock].first = i;
                        blocks[nBlock].last = i + u - 1;
                        blocks[nBlock].id = id;

                        FOR(j,i,i+u-1) canUse[j] = false;
                        break;
                    }
                }
                if (id < 0) cout << "NULL\n";
                else cout << id << '\n';
            }
            else if (typ == "erase") {
                int u; cin >> u;
                bool found = false;
                FOR(i,1,nBlock) if (blocks[i].id == u) {
                    FOR(j,blocks[i].first,blocks[i].last) canUse[j] = true;

                    found = true;
                    swap(blocks[i], blocks[nBlock]);
                    --nBlock;
                    break;
                }
                if (!found) cout << "ILLEGAL_ERASE_ARGUMENT\n";
            }
            else {
                sort(blocks+1, blocks+nBlock+1);
                int last = 0;
                FOR(i,1,nBlock) {
                    int len = blocks[i].last - blocks[i].first;

                    blocks[i].first = last + 1;
                    blocks[i].last = blocks[i].first + len;

                    last = blocks[i].last;
                }
                
                FOR(j,1,last) canUse[j] = false;
                FOR(j,last+1,avail) canUse[j] = true;
            }

//            PR(canUse, avail);
//            FOR(i,1,nBlock) cout << blocks[i].first << ' ' << blocks[i].last << "    "; cout << endl;
        }
    }
    return 0;
}

