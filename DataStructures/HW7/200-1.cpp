#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <list>

#define FOR(i, n) for(int i = 0; i < n; ++i)
#define LOOP(n) for(int I = 0; I < n; ++I)
#define diff(ch) (ch - 'A')

using namespace std;

/*
reference:
https://ppt.cc/fAirPx
https://ppt.cc/flbLOx
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
    string str1, str2;
    cin >> str1;

    int mem[26] = {}; // 1 -> 沒有小於其他字元，2 -> 有小於其他字元
    vector<int> G[26]; // 比 A 大的字元都會被推入 G[0]，...

    while (cin >> str2 && str2 != "#")
    {
        int l = min(str1.length(), str2.length());
        FOR(i, l)
        {
            if (!mem[diff(str1[i])]) mem[diff(str1[i])] = 1;
            if (!mem[diff(str2[i])]) mem[diff(str2[i])] = 1;

            if (str1[i] != str2[i])
            {
                G[diff(str1[i])].push_back(diff(str2[i]));
                mem[diff(str2[i])] = 2;
                break;
            }
        }
        str1 = str2;
    }

    int visited[26] = {}; // 1 -> 正在被 DFS，2 -> 已經 DFS 過了
    list<char> ret;

    function<void(int)> dfs = [&](int n)
    {
        if (visited[n] == 1) return; // 碰到環
        visited[n] = 1; // 正在被 DFS

        // 如果 visited[i] != 2 表示還沒被 DFS 過
        for (auto& i : G[n]) if (visited[i] != 2) dfs(i);
        visited[n] = 2;

        ret.push_front(n + 'A');
    };

    // 從沒有小於其他字元的字元開始 DFS
    FOR(i, 26) if (mem[i] == 1) dfs(i);

    for (auto& ch : ret) cout << ch;
    cout << '\n';
}