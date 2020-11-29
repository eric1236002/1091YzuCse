#include <iostream>
#include <functional>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <string>
#include <stack>
#include <map>

using namespace std;

/*
reference:
想法: https://ppt.cc/fc2nLx
Code: https://ppt.cc/fOJQux
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
    int n, m, Case = 0;
    int TIME;
    stack<string> s;
    map<string, int> dfn;
    map<string, int> low;
    unordered_set<string> inStack; // 紀錄目前存在 Stack 中的點
    map<string, vector<string>> G;

    // 找出 strong connected component
    function<void(string)> dfs = [&](string u)
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
            string tmp;
            while (true)
            {
                tmp = s.top();
                s.pop();
                inStack.erase(tmp);

                cout << tmp;
                if (tmp != u) cout << ", ";
                else break;
            }
            cout << '\n';
        }
    };

    while (cin >> n >> m && !(!n && !m))
    {
        // init
        TIME = 0;
        while (!s.empty()) s.pop();
        dfn.clear();
        low.clear();
        G.clear();
        inStack.clear();

        for (int i = 0; i < m; ++i)
        {
            string u, v;

            cin >> u >> v;
            G[u].push_back(v);
        }

        if (Case) cout << '\n';
        cout << "Calling circles for data set " << ++Case << ":\n";
        for (auto& [u, __] : G) if (!dfn[u]) dfs(u);
    }
}