//#pragma comment(linker, "/STACK:66777216")
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;
const double PI = acos(-1.0);

struct Node {
	string type;
	Node *left, *right;
} *root;

int n, cnt = 0;

Node* get() {
	string s;
	if (!(cin >> s)) return NULL;
	Node *p = new Node;
	p->type = s;
	p->left = p->right = NULL;

	if (s == "int") {
		++cnt;
		return p;
	}
	else {
		p->left = get();
		if (p->left == NULL) return NULL;
		p->right = get();
		if (p->right == NULL) return NULL;
		return p;
	}
}

void print(Node *root) {
	if (root->type == "int") {
		cout << root->type;
		return ;
	}
	cout << "pair<";
	print(root->left);
	cout << ",";
	print(root->right);
	cout << ">";
}

int main() {
	ios :: sync_with_stdio();
	cin >> n;
	root = get();
	string s;
	if (root == NULL || cnt != n || (cin >> s)) {
		puts("Error occurred");
		return 0;
	}
	print(root);
	cout << endl;
    return 0;
}
