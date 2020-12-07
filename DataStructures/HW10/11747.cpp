#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// reference: https://ppt.cc/f0psNx

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

    // 根據權重排序
    bool operator<(const edge& r) { return w < r.w; }
};

// data
int n, m; // input
vector<edge> edges;
int parents[1001]; // 每個點的 parent
int ranks[1001];

void init()
{
    edges.clear();
    // 一開始每個節點的 parent 都是自己，而 rank 皆為 0
    for (int i = 0; i < n; ++i) parents[i] = i, ranks[i] = 0;
}

int Find(int p) { return p == parents[p] ? p : parents[p] = Find(parents[p]); }

bool Union(int x, int y)
{
    int rx = Find(x), ry = Find(y);

    // 如果 x 跟 y 的 root 一樣，表示 x 和 y 接起會造成環
    if (rx == ry) return false;

    // 將 rank 較小的接到 rank 較大的樹下面，因為這樣後面 Find 時消耗較小
    if (ranks[x] > ranks[y]) parents[ry] = rx;
    else if (ranks[x] < ranks[y]) parents[rx] = ry;
    else parents[ry] = rx, ++ranks[rx];

    return true;
}

void kruskcal()
{
    bool isOut = false; // 是否已經有輸出

    for (auto& [u, v, w] : edges)
    {
        if (Union(u, v)) continue;

        // 若 u、v 已經連通了表示邊 (u, v) 是多餘的邊
        if (isOut) cout << ' ';
        cout << w;
        isOut = true;
    }

    if (!isOut) cout << "forest";
    cout << '\n';
}

int main()
{
    while (cin >> n >> m && !(!n && !m))
    {
        init();

        while (m--)
        {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({ u, v, w });
        }

        sort(edges.begin(), edges.end());

        kruskcal();
    }
}