#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>

using namespace std;

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int n, m;
int TIME;
int bcnt;
unordered_map<int, vector<int>> G;
unordered_map<int, int> dfn;
unordered_map<int, int> low;

void init()
{
    TIME = 0;
    bcnt = 0;
    G.clear();
    dfn.clear();
    low.clear();
}

void dfs(int u, int parent)
{
    dfn[u] = low[u] = ++TIME;

    for (auto& v : G[u])
    {
        if (!dfn[v])
        {
            dfs(v, u);
            low[u] = min(low[v], low[u]);
            if (low[v] > dfn[u]) ++bcnt;
        }
        else if (v != parent) low[u] = min(dfn[v], low[u]);
    }
}

void solve()
{
    if (bcnt == 1) { cout << "0\n"; return; }

    map<int, int> M;
    for (int u = 1; u <= n; ++u)
    {
        M[low[u]] += 0;
        for (auto& v : G[u]) if (low[u] != low[v]) ++M[low[u]];
    }

    int alone = 0, leaves = 0;
    for (auto& [_, de] : M)
    {
        if (!de) ++alone;
        else if (de == 1) ++leaves;
    }

    cout << (alone + (leaves + 1) / 2) << '\n';
}

int main()
{
    while (cin >> n >> m)
    {
        init();

        int u, v;
        while (m--) cin >> u >> v, G[u].push_back(v), G[v].push_back(u);

        for (int u = 1; u <= n; ++u) if (!dfn[u]) dfs(u, -1), ++bcnt;

        solve();
    }
}