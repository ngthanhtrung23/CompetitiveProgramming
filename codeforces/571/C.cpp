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

const int MN = 200111;

struct Clause {
    int nVar;
    set<int> vars;
    int ok;
} clauses[MN];

struct Var {
    int nClause;
    int clauses[3];
    int value;
} vars[MN];

int nVar, nClause;

set< pair<int,int> > allVar, allClause;
void init() {
    memset(vars, 0, sizeof vars);
    allVar.clear();
    allClause.clear();
    FOR(i,1,nVar) {
        vars[i].value = -1;
    }
    FOR(i,1,nClause) {
        clauses[i].nVar = 0;
        clauses[i].vars.clear();
        clauses[i].ok = 0;
    }
}


void removeClause(int cl) {
    allClause.erase(make_pair(clauses[cl].nVar, cl));
    for(auto t : clauses[cl].vars) {
        int v = abs(t);
        if (vars[v].value >= 0) continue;

        allVar.erase(make_pair(vars[v].nClause, v));
        vars[v].nClause--;
        if (vars[v].nClause == 1 && vars[v].clauses[1] == cl) {
            vars[v].clauses[1] = vars[v].clauses[2];
        }
        allVar.insert(make_pair(vars[v].nClause, v));
    }
}

void processVar(int var) {
    if (var < 0) var = -var;
//    DEBUG(var);
    int cnt = vars[var].nClause;
    allVar.erase(make_pair(cnt, var));

    if (cnt == 0) {
        vars[var].value = 1;
    }
    else if (cnt == 1) {
        int cl = vars[var].clauses[1];
        assert(!clauses[cl].ok);
        if (clauses[cl].vars.count(var)) {
            vars[var].value = 1;
        }
        else {
            vars[var].value = 0;
        }
        clauses[cl].ok = true;
        removeClause(cl);
    }
    else if (cnt == 2) {
        int cl1 = vars[var].clauses[1];
        int cl2 = vars[var].clauses[2];
        assert(!clauses[cl1].ok);
        assert(!clauses[cl2].ok);

        if (clauses[cl1].nVar > clauses[cl2].nVar) {
            swap(cl1, cl2);
        }
        
        if (clauses[cl1].vars.count(var)) {
            vars[var].value = 1;
        }
        else {
            vars[var].value = 0;
        }
        clauses[cl1].ok = true;
        removeClause(cl1);

        if ((clauses[cl2].vars.count(var) && vars[var].value == 1)
                || (clauses[cl2].vars.count(-var) && vars[var].value == 0)) {
            clauses[cl2].ok = true;
            removeClause(cl2);
        }
        else {
            allClause.erase(make_pair(clauses[cl2].nVar, cl2));
            clauses[cl2].nVar--;
            clauses[cl2].vars.erase(var);
            clauses[cl2].vars.erase(-var);
            allClause.insert(make_pair(clauses[cl2].nVar, cl2));
        }
    }
//    DEBUG(vars[var].value);
}
void solve() {
    FOR(i,1,nVar) allVar.insert(make_pair(vars[i].nClause, i));
    FOR(i,1,nClause) allClause.insert(make_pair(clauses[i].nVar, i));

    while (!allVar.empty()) {
//        cout << "vars = ";
//        for(auto var : allVar) cout << var.second << " (" << var.first << ")  "; cout << endl;
//        cout << "clauses = ";
//        for(auto p : allClause) cout << p.second << " (" << p.first << ")  "; cout << endl;

        if (allVar.begin()->first < 2) {
            int var = allVar.begin()->second;
            processVar(var);
        }
        else if (allClause.begin()->first < 2) {
            int cl = allClause.begin()->second;
            assert(!clauses[cl].ok);

            if (clauses[cl].nVar == 0) {
                puts("NO");
                return ;
            }

            int var = *clauses[cl].vars.begin();
            processVar(var);
        }
        else {
            int var = allVar.begin()->second;
            processVar(var);
        }
    }

    FOR(i,1,nClause) if (!clauses[i].ok) {
        puts("NO");
        return ;
    }
    puts("YES");
    FOR(i,1,nVar) printf("%d", vars[i].value);
    puts("");
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> nClause >> nVar) {
        init();
        FOR(i,1,nClause) {
            int k; cin >> k;
            REP(j,k) {
                int x; cin >> x;
                clauses[i].vars.insert(x);

                if (x < 0) x = -x;
                vars[x].nClause++;
                vars[x].clauses[ vars[x].nClause ] = i;
            }
            clauses[i].nVar = k;
        }
        solve();
    }
}
