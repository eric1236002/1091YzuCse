#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <map>

using namespace std;

/*
reference:
題目: https://ppt.cc/fkzEYx
解題想法: https://ppt.cc/fbXXcx
雙連通分量: https://ppt.cc/fs5cxx
Code: https://ppt.cc/fsPeKx
*/

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
};

int TIME;
int comSize;               // 目前遍歷的 Biconnected component 的節點數
map<int, int> dfn;
map<int, int> low;
map<int, vector<int>> G;
unordered_set<int> isCut;  // 儲存所有割點
unordered_set<int> visited;
unordered_set<int> adjCut; // 一個 Biconnected component 連接到的割點

void dfs(int u, int parent)
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

        // 記錄所有割點
        if (low[v] >= dfn[u] && (child >= 2 || parent != -1)) isCut.insert(u);
    }
}

void findAns(int u)
{
    visited.insert(u);
    ++comSize;

    for (auto& v : G[u])
    {
        if (visited.count(v) || isCut.count(v))
        {
            // 如果 v 是割點
            if (isCut.count(v)) adjCut.insert(v);
            continue;
        }

        findAns(v);
    }
}

int main()
{
    int N, Case = 0;

    while (cin >> N && N)
    {
        // init
        TIME = 0;
        dfn.clear();
        low.clear();
        G.clear();
        isCut.clear();
        visited.clear();

        // build the graph
        for (int i = 0; i < N; ++i)
        {
            int u, v;
            cin >> u >> v;

            G[u].push_back(v);
            G[v].push_back(u);
        }

        // 尋找所有割點
        for (auto& [u, __] : G) if (!dfn[u]) dfs(u, -1);

        vector<int> D; // 儲存每個 Biconnected component 的節點數量
        for (auto& [u, __] : G)
        {
            if (visited.count(u) || isCut.count(u)) continue;

            comSize = 0;
            adjCut.clear();
            findAns(u);

            // 如果遍歷到的 Biconnected component 只連接到一個割點才需要有標記點
            if (adjCut.size() == 1) D.push_back(comSize);
        }

        // Biconnected component 的個數代表最少需要有幾個標記點 ( 個數不為 1 的情況 )
        long long ways = 1, mn = D.size();
        for (auto& i : D) ways *= i;

        // 如果整個圖本身為一個 Biconnected component，則任選兩點標記，mn 為 2
        if (D.empty()) ways = (long long)G.size() * (G.size() - 1) / 2, mn = 2;

        cout << "Case " << ++Case << ": " << mn << " " << ways << '\n';
    }
}