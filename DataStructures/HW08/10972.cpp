#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

/* reference:
想法: https://ppt.cc/fXERhx
Code: https://ppt.cc/fNsXNx
*/

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int n, m;      // input
int TIME;
int bcnt;      // bridge connected component 的數量
int dfn[1001]; // dfs 時的序號
int low[1001]; // dfs 時的 low 值
vector<int> G[1001];

// 找出 bridge connected component
void dfs(int u, int parent)
{
    dfn[u] = low[u] = ++TIME;

    for (auto& v : G[u])
    {
        if (dfn[v])
        {
            if (v != parent) low[u] = min(dfn[v], low[u]);
            continue;
        }

        dfs(v, u);
        low[u] = min(low[v], low[u]);

        // 找到一個橋，bridge connected component 的數量加一
        if (low[v] > dfn[u]) ++bcnt;
    }
}

void solve()
{
    // 如果整張圖本身就是一個 bridge connected component ( 沒有橋 )，則不需要新增邊
    if (bcnt == 1) { cout << 0 << '\n'; return; }

    // 每一組 bridge connected component 連接到的 bridge connected component 數量 -> degree
    map<int, int> m;
    for (int u = 1; u <= n; ++u)
    {
        m[low[u]] += 0; // 單獨一個 bridge connected component -> degree = 0
        for (auto& v : G[u]) if (low[v] != low[u]) ++m[low[u]];
    }

    int alone = 0, leaves = 0;
    for (auto& [u, de] : m)
    {
        if (!de) ++alone;
        else if (de == 1) ++leaves;
    }

    cout << alone + (leaves + 1) / 2 << '\n';
}

int main()
{
    while (cin >> n >> m)
    {
        // init
        TIME = 0;
        bcnt = 0;
        fill(dfn, dfn + 1001, 0);
        fill(low, low + 1001, 0);
        fill(G, G + 1001, vector<int>());

        while (m--)
        {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        // 找出 bridge connected component 的數量
        for (int i = 1; i <= n; ++i)
        {
            if (!dfn[i])
            {
                dfs(i, -1);

                // 對於一個連通圖來說，若沒有橋則本身是 bridge connected component
                // 否則若圖中有一個橋，則圖會被分為兩個 bridge connected component
                // 所以這邊需要加一
                ++bcnt;
            }
        }

        solve();
    }
}