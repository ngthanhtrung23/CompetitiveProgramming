
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

int nNote, nSp;
int notes[50111];
pair<int,int> sp[111];
int f[111];
int sumSpBeforeNote[50111], sumSp[111], nextSpAfterNote[50111];
int lastNoteBeforeSp[111];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &nNote, &nSp) == 2) {
        FOR(i,1,nNote) scanf("%d", &notes[i]);
        FOR(i,1,nSp) scanf("%d%d", &sp[i].first, &sp[i].second);

        ++nSp;
        sp[nSp] = make_pair(50111000, 50222000);

        FOR(i,1,nSp) sumSp[i] = sumSp[i-1] + sp[i].second - sp[i].first;

        FOR(i,1,nNote) {
            sumSpBeforeNote[i] = 0;
            FOR(j,1,nSp)
                if (sp[j].first <= notes[i]) {
                    sumSpBeforeNote[i] += min(notes[i], sp[j].second) - sp[j].first;
                }

            FOR(j,1,nSp) {
                if (notes[i] < sp[j].first) {
                    nextSpAfterNote[i] = j;
                    break;
                }
            }
        }

        FORD(i,nSp,1) {
            f[i] = 0;
            int j = 1;
            while (j <= nNote && notes[j] < sp[i].first) ++j;
            if (j > nNote) continue;

//            DEBUG(i);

            int jj = j;
            while (j <= nNote) {
                while (jj <= j
                        && notes[j] - notes[jj] + 1 > sumSpBeforeNote[jj] - sumSp[i-1])
                    ++jj;

                if (jj <= j) {
//                    cout << jj << " --> " << j << ", need = " << notes[j] - notes[jj] + 1
//                        << ", has = " << sumSpBeforeNote[jj] - sumSp[i-1]
//                        << endl;
                    f[i] = max(f[i], f[nextSpAfterNote[j]] + j - jj + 1);
                }
                ++j;
            }
//            DEBUG(f[i]);
        }

        cout << f[1] + nNote << endl;
    }
}
