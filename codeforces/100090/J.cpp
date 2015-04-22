
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

struct Node {
    int x;
    Node* next, *prev;

    Node(int x = 0) : x(x), next(NULL), prev(NULL) {}
} *head, *tail;

void append(int x) {
    if (head == NULL) {
        head = tail = new Node(x);
        return ;
    }
    Node *tmp = new Node(x);
    tail->next = tmp;
    tmp->prev = tail;
    tail = tmp;
}
int a[200111];
char tmp[1011];

int main() {
    int n, p;
    while (scanf("%d%d", &n, &p) == 2) {
        head = tail = NULL;
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            append(a[i]);
        }
        int q; scanf("%d", &q);
        --p;
        Node* cur = head;
        while (p--) {
            cur = cur->next;
        }
        while (q--) {
            scanf("%s", tmp);
            if (tmp[0] == 'p') {
                printf("%d\n", cur->x);
            }
            else if (tmp[4] == 'L') {
                if (cur->prev) cur = cur->prev;
            }
            else if (tmp[4] == 'R') {
                if (cur->next) cur = cur->next;
            }
            else if (tmp[6] == 'L') {
                int tmp; scanf("%d", &tmp);
                if (cur->prev) {
                    Node *x = cur->prev;
                    Node *y = new Node(tmp);

                    y->next = cur;
                    cur->prev = y;

                    x->next = y;
                    y->prev = x;
                }
                else {
                    Node *y = new Node(tmp);
                    y->next = cur;
                    cur->prev = y;
                }
            }
            else {
                int tmp; scanf("%d", &tmp);
                if (cur->next) {
                    Node *x = cur->next;
                    Node *y = new Node(tmp);

                    y->next = x;
                    x->prev = y;

                    cur->next = y;
                    y->prev = cur;
                }
                else {
                    Node *y = new Node(tmp);
                    cur->next = y;
                    y->prev = cur;
                }
            }
        }
    }
    return 0;
}
