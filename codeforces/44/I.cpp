#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

vector <vector <vector <int> > > L[15];
int n;
vector <int> last, bef;

int main () {
  //  freopen ("test.in", "r", stdin);
  //  freopen ("test.out", "w", stdout);
    
    scanf ("%d", &n);
    
    vector <int> v1;
    v1.push_back (1);
    vector <vector <int> > v2;
    v2.push_back (v1);
    vector <vector <vector <int> > > v3;
    v3.push_back (v2);
    
    L[1] = v3;
    
    v2.clear ();
    
    for (int i = 2; i <= n; i++) {
        for (int p = 0; p < L[i - 1].size(); p++) {
            vector <vector <int> > TMP;
            // from outside
            if (p % 2 != 0) {
                L[i].push_back (L[i - 1][p]);
                vector <int> v;
                v.push_back (i);
                L[i][L[i].size() - 1].push_back (v);
            }
            
            int idx = -1;
            int mx = -1;
            
            for (int j = 0; j < L[i - 1][p].size(); j++) {
                int ctr = 0;
                for (int k = 0; k < L[i - 1][p][j].size(); k++) {
                    bool same = false;
                    for (int xx = 0; xx < last.size(); xx++) {
                        if (L[i - 1][p][j][k] == last[xx]) {
                            same = true;
                            break;
                        }
                    }
                    if (!same) {
                        ctr = -2;
                        break;
                    }
                }
                if (ctr > mx) {
                    idx = j;
                    mx = ctr;
                }
                ctr = 0;
                for (int xx = 0; xx < last.size(); xx++) {
                    bool same = false;
                    for (int k = 0; k < L[i - 1][p][j].size(); k++) {
                        if (L[i - 1][p][j][k] == last[xx]) {
                            same = true;
                            break;
                        }
                    }
                    if (!same) {
                        ctr = -2;
                        break;
                    }
                }
                if (ctr > mx) {
                    idx = j;
                    mx = ctr;
                }
            }
            
            for (int j = 0; j < L[i - 1][p].size(); j++) {
                if (j != idx) continue;
                TMP.clear ();
                for (int k = 0; k < L[i - 1][p].size(); k++) {
                    TMP.push_back (L[i - 1][p][k]);
                    if (k == j) {
                        bef = L[i - 1][p][k];
                        TMP[TMP.size() - 1].push_back (i);
                    }
                }
                L[i].push_back (TMP);
            }
            
            for (int j = 0; j < L[i - 1][p].size(); j++) {
                if (j == idx) continue;
                TMP.clear ();
                for (int k = 0; k < L[i - 1][p].size(); k++) {
                    TMP.push_back (L[i - 1][p][k]);
                    if (k == j) {
                        bef = L[i - 1][p][k];
                        TMP[TMP.size() - 1].push_back (i);
                    }
                }
                L[i].push_back (TMP);
            }
            last = bef;
            // from inside
            if (p % 2 == 0) {
                L[i].push_back (L[i - 1][p]);
                vector <int> v;
                v.push_back (i);
                L[i][L[i].size() - 1].push_back (v);
            }
            /*
           if (i == n) L[i].push_back (v2);
           if (i == n) {
                v1.clear();
                v1.push_back (idx);
                v1.push_back (mx);
                v2.push_back (v1);
                v1.clear();
                v2.push_back (last);
                L[i].push_back (v2);
                v2.clear();
            }
            */
          //  if (i == n) L[i].push_back (v2);
        }
    }
    
    printf ("%d\n", L[n].size());
    for (int i = 0; i < L[n].size(); i++) {
        for (int j = 0; j < L[n][i].size(); j++) {
            sort (L[n][i][j].begin(), L[n][i][j].end());
        }
        sort (L[n][i].begin(), L[n][i].end());
        for (int j = 0; j < L[n][i].size(); j++) {
            if (j) printf (",");
            printf ("{");
            for (int k = 0; k < L[n][i][j].size(); k++) {
                if (k) printf (",");
                printf ("%d", L[n][i][j][k]);
            }
            printf ("}");
        }
        puts ("");
    }
    
    return 0;
}
