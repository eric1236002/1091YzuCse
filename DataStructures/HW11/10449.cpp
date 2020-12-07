#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
};

// data
int busyness[201];
int dist[201];
vector<pair<int, int>> edges[201];
unordered_set<int> s;

void init()
{
    s.clear();
    fill(dist, dist + 201, INT_MAX);
    fill(edges, edges + 201, vector<pair<int, int>>());
}

void bellman(int n)
{
    // 從 1 開始
    dist[1] = 0;

    // 若不存在負環，則做 n - 1 次後 dist 會儲存 0 到每個點的最短路徑
    for (int i = 0; i < n - 1; ++i) for (int u = 1; u <= n; ++u)
    {
        for (auto& [v, w] : edges[u])
            if (dist[u] != INT_MAX) dist[v] = min(dist[u] + w, dist[v]);
    }

    for (int u = 1; u <= n; ++u) for (auto& [v, w] : edges[u])
    {
        // 如果 v 還能變小，表示 v 可以無限變小
        if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
        {
            dist[v] = dist[u] + w;
            s.insert(v);
        }
    }
}

int main()
{
    int n, Case = 0;
    while (cin >> n)
    {
        init();

        for (int i = 1; i <= n; ++i)
        {
            int b;
            cin >> b;
            busyness[i] = b;
        }

        int m;
        cin >> m;

        while (m--)
        {
            int u, v;
            cin >> u >> v;
            edges[u].push_back({ v, (int)pow(busyness[v] - busyness[u], 3) });
        }

        bellman(n);

        int q;
        cin >> q;

        cout << "Set #" << ++Case << '\n';
        while (q--)
        {
            int p;
            cin >> p;
            if (s.count(p) || dist[p] < 3 || dist[p] == INT_MAX) cout << "?\n";
            else cout << dist[p] << '\n';
        }
    }
}