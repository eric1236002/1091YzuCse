#include <iostream>
#include <functional>
#include <climits>
#include <vector>

#define LOOP(n) for(int I = 0; I < n; ++I)

using namespace std;

// reference: https://ppt.cc/fXuBwx

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int main()
{
    int T;
    cin >> T;

    LOOP(T)
    {
        int N;
        cin >> N;

        vector<int> adj(N + 1);
        LOOP(N)
        {
            int u, v;
            cin >> u >> v;
            adj[u] = v;
        }

        int _max = INT_MIN, ret = 0;
        vector<bool> visited(N + 1), dfsV;

        function<int(int)> dfs = [&](int u) -> int
        {
            // 如果已經寄過了就直接回傳，避免環
            if (dfsV[u]) return 0;
            visited[u] = dfsV[u] = true;
            return 1 + dfs(adj[u]);
        };

        for (int i = 1; i <= N; ++i)
        {
            // 如果 i 在前面被做過一次那就不用再做一次了，因為前面是從某個人寄到 i，
            // 一定會比直接寄到 i 還要多人
            if (visited[i]) continue;

            dfsV.assign(N + 1, false);
            int tmp = dfs(i);
            if (tmp > _max) _max = tmp, ret = i;
        }

        cout << "Case " << I + 1 << ": " << ret << '\n';
    }
}