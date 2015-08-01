
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

char tmp[100111];

struct Product {
    string name;
    int nIngredient;
    vector<string> ingredients;
    vector<int> left, right;

    map<string,int> id;

    void read() {
        gets(tmp); name = string(tmp);

        scanf("%d\n", &nIngredient);

        ingredients.resize(nIngredient + 5);
        left.resize(nIngredient + 5);
        right.resize(nIngredient + 5);
        id.clear();

        REP(i,nIngredient) {
            gets(tmp);
            stringstream ss(tmp);
            string cur; ss >> cur;

            left[i] = 1; right[i] = 100;
            ingredients[i] = cur;
            id[ ingredients[i] ] = i + 1;

            int p;
            if (ss >> p) {
                left[i] = right[i] = p;
            }
        }
    }

    void print() {
        DEBUG(name);
        REP(i,nIngredient) {
            cout << ingredients[i] << ": " << left[i] << ' ' << right[i] << endl;
        }
    }

    void refine() {
        REP(turn,1500) {
            FORD(i,nIngredient-2,0) left[i] = max(left[i], left[i+1]);
            REP(i,nIngredient) if (i) right[i] = min(right[i], right[i-1]);

            REP(i,nIngredient) {
                int can = 100;
                REP(j,nIngredient) if (i != j) {
                    can -= left[j];
                }
                right[i] = min(right[i], can);

                can = 0;
                REP(j,nIngredient) if (i != j) {
                    can += right[j];
                }
                left[i] = max(left[i], 100 - can);
            }

            // update left[i]
            REP(i,nIngredient) {
                int maxSum = 0;
                REP(j,i) maxSum += right[j];
                maxSum += left[i];

                FOR(j,i+1,nIngredient-1) maxSum += min(left[i], right[j]);

                if (maxSum < 100) ++left[i];
            }
            
            // update right[i]
            REP(i,nIngredient) {
                int minSum = 0;
                REP(j,i) minSum += max(right[i], left[j]);
                minSum += right[i];
                FOR(j,i+1,nIngredient-1) minSum += left[j];

                if (minSum > 100) --right[i];
            }
        }
    }
} a[11];

int n;

int main() {
    while (scanf("%d\n", &n) == 1 && n) {
        FOR(i,1,n) {
            a[i].read();
            a[i].refine();
//            a[i].print();
        }
        int q; scanf("%d\n", &q);
        while (q--) {
            gets(tmp);
            string typ, ing; stringstream ss(tmp); ss >> typ >> ing;

            vector<string> res;
            FOR(i,1,n) {
                int cur;

                if (a[i].id.count(ing)) {
                    int i_id = a[i].id[ing] - 1;
                    if (typ == "most") cur = a[i].right[i_id];
                    else cur = a[i].left[i_id];
                }
                else cur = 0;

                bool ok = true;
                FOR(j,1,n) if (i != j) {
                    int cur_j;

                    if (a[j].id.count(ing)) {
                        int j_id = a[j].id[ing] - 1;
                        if (typ == "most") cur_j = a[j].left[j_id];
                        else cur_j = a[j].right[j_id];
                    }
                    else cur_j = 0;

                    if (typ == "most" && cur_j > cur) {
                        ok = false;
                        break;
                    }
                    if (typ == "least" && cur_j < cur) {
                        ok = false;
                        break;
                    }
                }

                if (ok) res.push_back(a[i].name);
            }

            for(auto s : res) cout << s << ' ';
            cout << endl;
        }
    }
}
