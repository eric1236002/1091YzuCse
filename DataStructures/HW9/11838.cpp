#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <stack>

using namespace std;

// reference: https://ppt.cc/fkxbXx

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int TIME;
int cnt;
vector<int> dfn;
vector<int> low;
unordered_set<int> inStack;
vector<vector<int>> G;
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
            inStack.erase(tmp);
        } while (tmp != u);
        ++cnt;
    }
}

int main()
{
    int N, M;
    while (cin >> N >> M && !(!N && !M))
    {
        // init
        TIME = 0;
        cnt = 0;
        dfn.assign(N + 1, 0);
        low.assign(N + 1, 0);
        inStack.clear();
        G.assign(N + 1, vector<int>());
        while (!s.empty()) s.pop();

        while (M--)
        {
            int u, v, P; // P 為 1 代表單向 u -> v，為 2 代表雙向 u -> v, v -> u
            cin >> u >> v >> P;

            G[u].push_back(v);
            if (P == 2) G[v].push_back(u);
        }

        for (int u = 1; u <= N; ++u) if (!dfn[u] && cnt < 2) dfs(u);

        cout << (cnt == 1) << '\n';
    }
}