#include <iostream>
#include <climits>
#include <queue>
#include <unordered_map>

using namespace std;

// reference: https://ppt.cc/ffqNmx

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

unordered_map<int, vector<pair<int, int>>> edges;
int value[20000];
bool visited[20000];
priority_queue<point, vector<point>, greater<point>> pq;

void init(int n)
{
    edges.clear();
    for (int i = 0; i < n; ++i) value[i] = INT_MAX, visited[i] = false;
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
    int T, Case = 0;
    cin >> T;

    while (T--)
    {
        int n, m, s, t;
        cin >> n >> m >> s >> t;
        init(n);

        while (m--)
        {
            int u, v, w;
            cin >> u >> v >> w;

            // 雙向建邊
            edges[u].push_back({ v, w });
            edges[v].push_back({ u, w });
        }

        dijkstra(s);

        cout << "Case #" << ++Case << ": ";
        if (value[t] != INT_MAX) cout << value[t] << '\n';
        else cout << "unreachable\n";
    }
}