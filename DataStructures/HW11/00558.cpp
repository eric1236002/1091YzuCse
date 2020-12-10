#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

struct edge
{
    int u;
    int v;
    int w;
};

// data
vector<edge> edges;
int dist[1000];

void init(int n)
{
    edges.clear();
    fill(dist, dist + n, INT_MAX);
}

// 如果有負環則回傳 true
bool bellman(int n)
{
    // 從 0 開始
    dist[0] = 0;

    // 若不存在負環，則做 n - 1 次後 dist 會儲存 0 到每個點的最短路徑
    for (int i = 0; i < n - 1; ++i) for (auto& [u, v, w] : edges)
        if (dist[u] != INT_MAX) dist[v] = min(dist[u] + w, dist[v]);

    // 若任意點還能再更短則表示有負環
    for (auto& [u, v, w] : edges) if (dist[v] > dist[u] + w) return true;

    return false;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int n, m;
        cin >> n >> m;
        init(n);

        // 建圖
        while (m--)
        {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({ u, v, w });
        }

        if (bellman(n)) cout << "possible\n";
        else cout << "not possible\n";
    }
}