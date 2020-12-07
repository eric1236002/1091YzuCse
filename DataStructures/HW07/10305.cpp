#include <iostream>
#include <functional>
#include <vector>
#include <list>

using namespace std;

#define LOOP(n) for(int I = 0; I < n; ++I)
#define SIZE(c) int(c.size())

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int main()
{
    int N, M;
    int mem[101]; // 0 -> 沒有被其他點連入，1 -> 被其他點連入
    int visited[101];
    vector<int> G[101];
    list<int> ret;

    function<void(int)> dfs = [&](int n)
    {
        if (visited[n]) return;
        visited[n] = 1;
        for (auto& i : G[n]) dfs(i);
        ret.push_front(n);
    };

    while (cin >> N >> M && (N || M))
    {
        // init
        ret.clear();
        fill(mem, mem + 101, 0);
        fill(visited, visited + 101, 0);
        fill(G, G + 101, vector<int>());

        LOOP(M)
        {
            int a, b;
            cin >> a >> b;
            G[a].push_back(b);
            mem[b] = 1;
        }

        for (int i = 1; i <= N; ++i) if (!mem[i]) dfs(i);

        cout << ret.front();
        for (auto it = ++ret.begin(); it != ret.end(); ++it) cout << " " << *it;
        cout << '\n';
    }
}