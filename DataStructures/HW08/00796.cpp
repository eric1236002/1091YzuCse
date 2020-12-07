#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>

using namespace std;

// reference: https://ppt.cc/fzjSzx

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int main()
{
    int N;
    int time;
    vector<vector<int>> G;
    vector<int> dfsD;
    vector<int> low;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // parent 為 -1 代表沒有 parent
    function<void(int, int)> dfs = [&](int n, int parent)
    {
        dfsD[n] = low[n] = ++time;

        for (auto& i : G[n])
        {
            if (dfsD[i])
            {
                if (parent != i) low[n] = min(dfsD[i], low[n]);
                continue;
            }

            dfs(i, n);
            low[n] = min(low[i], low[n]);

            // 如果 low[i] 大於 dfsD[n] 表示 i 及 i 的 descendant 沒有 backedge
            // 連接到 n 的 ancestor ( 包含 n )，則 ( u, v ) 為 bridge
            // 由於題目要求較小的放在前面，所以這樣存入
            if (low[i] > dfsD[n]) pq.push({ min(n, i), max(n, i) });
        }
    };

    while (cin >> N)
    {
        // init
        time = 0;
        G.assign(N, vector<int>());
        dfsD.assign(N, 0);
        low.assign(N, 0);
        // pq 每次結束後都會清空

        for (int i = 0; i < N; ++i)
        {
            int a, b, n;
            char ch;
            cin >> a >> ch >> n >> ch;

            // 雖然是無向圖，但是測資給的是點的所有連接情況，如果這邊建雙向的話會造成重複
            // 如 (1, 5) 及 (5, 1) 所以這裡建單向即可，這樣建出來的圖最後即是雙向的
            while (n--) cin >> b, G[a].push_back(b);
        }

        for (int i = 0; i < N; ++i) if (!dfsD[i]) dfs(i, -1);
        
        cout << pq.size() << " critical links" << '\n';
        while (!pq.empty())
        {
            cout << pq.top().first << " - " << pq.top().second << '\n';
            pq.pop();
        }
        cout << '\n';
    }
}