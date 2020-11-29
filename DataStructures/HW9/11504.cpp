#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <stack>

using namespace std;

/*
reference:
https://ppt.cc/fMdaHx
https://ppt.cc/fnAeqx
*/

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int TIME;
int cnt;         // 計算目前有幾個 scc
vector<int> dfn;
vector<int> low;
vector<int> com; // 紀錄點屬於哪個 scc
vector<vector<int>> G;
unordered_set<int> inStack;
stack<int> s;

void dfs(int u)
{
    dfn[u] = low[u] = ++TIME;
    s.push(u);
    inStack.insert(u);

    for (auto& v : G[u])
    {
        if (dfn[v])
        {
            if (inStack.count(v)) low[u] = min(dfn[v], low[u]);
            continue;
        }

        dfs(v);
        low[u] = min(low[v], low[u]);
    }

    if (dfn[u] == low[u])
    {
        int tmp;
        do
        {
            tmp = s.top();
            s.pop();
            com[tmp] = cnt;
            inStack.erase(tmp);
        } while (tmp != u);
        ++cnt;
    }
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int n, m;
        cin >> n >> m;

        // init
        TIME = 0;
        cnt = 0;
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        com.assign(n + 1, 0);
        G.assign(n + 1, vector<int>());
        inStack.clear();
        while (!s.empty()) s.pop();

        while (m--)
        {
            int u, v;
            cin >> u >> v;

            G[u].push_back(v);
        }

        // 找出 scc ( strongly connected component )
        for (int u = 1; u <= n; ++u) if (!dfn[u]) dfs(u);

        // 計算 scc 被幾個其他的 scc 接入
        vector<int> degree(cnt);
        for (int u = 1; u <= n; ++u) for (auto& v : G[u])
        {
            if (com[u] != com[v]) ++degree[com[v]];
        }

        int ret = 0;
        // 如果 scc 沒有被其他的 scc 接入則需要一次來推倒
        for (auto& de : degree) if (!de) ++ret;
        cout << ret << '\n';
    }
}