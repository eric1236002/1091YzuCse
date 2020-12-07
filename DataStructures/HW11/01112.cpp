#include <iostream>
#include <climits>
#include <queue>
#include <unordered_map>

using namespace std;

// reference: https://ppt.cc/fU8XZx

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

struct point
{
    int u;
    int w;

    bool operator>(const point& r) const { return w > r.w; }
};

// data
unordered_map<int, vector<pair<int, int>>> edges;
int value[101];
bool visited[101];
priority_queue<point, vector<point>, greater<point>> pq;

void init(int n)
{
    edges.clear();
    for (int i = 1; i <= n; ++i) value[i] = INT_MAX, visited[i] = false;
}

void dijkstra(int start)
{
    pq.push({ start, value[start] = 0 });

    while (!pq.empty())
    {
        auto [u, val] = pq.top();
        visited[u] = true;
        pq.pop();

        for (auto& [v, w] : edges[u])
        {
            if (visited[v]) continue;
            int tmp = val + w;
            if (value[v] > tmp) pq.push({ v, value[v] = tmp });
        }
    }
}

int main()
{
    int T;
    cin >> T;
    
    while (T--)
    {
        int n, end, time, m;
        cin >> n >> end >> time >> m;
        init(n);
        
        while (m--)
        {
            int u, v, w;
            cin >> u >> v >> w;

            // 反向建邊
            edges[v].push_back({ u, w });
        }

        // 從終點開始
        dijkstra(end);

        int ret = 0;
        for (int i = 1; i <= n; ++i) if (value[i] <= time) ++ret;

        cout << ret << '\n';
        if (T) cout << '\n';
    }
}