#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

/*
reference:
https://ppt.cc/foedPx
https://ppt.cc/fxMzyx
*/

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int main()
{
    int n, m;
    int TIME;
    vector<int> dfn;
    vector<int> low;
    vector<int> cnt;
    vector<vector<int>> G;
    vector<pair<int, int>> ret;

    function<void(int, int)> dfs = [&](int u, int parent)
    {
        int child = 0;

        dfn[u] = low[u] = ++TIME;

        for (auto& v : G[u])
        {
            if (dfn[v])
            {
                if (v != parent) low[u] = min(dfn[v], low[u]);
                continue;
            }

            ++child;
            dfs(v, u);
            low[u] = min(low[v], low[u]);

            // 紀錄有幾個點將 u 視為割點
            if (low[v] >= dfn[u] && (child >= 2 || parent != -1)) ++cnt[u];
        }
    };

    while (cin >> n >> m && (n || m))
    {
        // init
        TIME = 0;
        dfn.assign(n, 0);
        low.assign(n, 0);
        cnt.assign(n, 0);
        G.assign(n, vector<int>());
        ret.clear();

        int u, v;
        while (cin >> u >> v && !(u == -1 && v == -1))
        {   // 無向圖，建雙向邊
            G[u].push_back(v);
            G[v].push_back(u);
        }

        for (int i = 0; i < n; ++i) if (!dfn[i]) dfs(i, -1);

        // 最後要加一是因為若有一個節點將此點視為割點，則拿掉此點
        // 圖會被分為兩部分，若有 n 個，則為 n + 1
        for (int i = 0; i < n; ++i) ret.push_back({ i, cnt[i] + 1 });

        // 根據題目的要求排序 ( 值較大的在上面，若值相等則序號較小的在上面 )
        auto cmp = [](pair<int, int>& l, pair<int, int>& r)
        {
            return l.second != r.second ? l.second > r.second : l.first < r.first;
        };
        sort(begin(ret), end(ret), cmp);

        for (int i = 0; i < m; ++i) cout << ret[i].first << " " << ret[i].second << '\n';
        cout << '\n';
    }
}