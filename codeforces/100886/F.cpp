#include <bits/stdc++.h>
using namespace std;

int n, target, f[33333];
pair <int,int> a[22];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> target;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].first;
        a[i].second = i;

        if (a[i].first == target) {
            cout << 1 << endl;
            cout << 1 << ' ' << i << endl;
            return 0;
        }
    }

    sort(a + 1, a + n + 1);
    queue <int> q;
    f[0] = 1;
    q.push(0);
    while (!q.empty() && !f[target])
    {
        int x = q.front();
        q.pop();
        for (int i = 1; i < n; i++)
        {
            int y = (x + a[i].first) % a[n].first;
            if (!f[y])
            {
                f[y] = i;
                q.push(y);
            }
        }
    }

    if (!f[target]) cout << -1 << endl;
    else
    {
        vector <int> trace;
        int x = target;
        while (x)
        {
            trace.push_back(f[x]);
            x = (x - a[f[x]].first + a[n].first) % a[n].first;
        }

        reverse(trace.begin(), trace.end());
        vector <int> type;
        vector < pair<int,int> > ves;
        for (int id : trace)
        {
            x += a[id].first;
            type.push_back(1);
            ves.push_back({a[id].second, 0});
            type.push_back(3);
            ves.push_back({a[id].second, a[n].second});
            if (x >= a[n].first)
            {
                type.push_back(2);
                ves.push_back({a[n].second, 0});
                if (x > a[n].first)
                {
                    type.push_back(3);
                    ves.push_back({a[id].second, a[n].second});
                }
                x %= a[n].first;
            }
        }

        cout << type.size() << endl;
        for (int i = 0; i < type.size(); i++)
        {
            cout << type[i] << ' ' << ves[i].first;
            if (type[i] == 3) cout << ' ' << ves[i].second;
            cout << '\n';
        }
    }
}
