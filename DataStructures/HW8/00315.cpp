#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <functional>

using namespace std;

/* reference:
https://ppt.cc/fuwZGx
https://ppt.cc/fUny8x
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
    int N; // 點的數量
    int time; // dfs 的順序
    int ret;
    string str;
    stringstream ss;
    vector<vector<int>> G;
    vector<int> dfsD;
    vector<int> low;

    // parent 為 0 表示 n 為 root
    function<void(int, int)> dfs = [&](int n, int parent)
    {
        int child = 0;
        bool flag = false;

        dfsD[n] = low[n] = ++time;

        for (auto& i : G[n])
        {
            // 如果不為 0 表示遍歷過了
            if (dfsD[i])
            {   // 若 i 不為 n 的 parent 才能更新 low 值
                if (parent != i) low[n] = min(dfsD[i], low[n]);
                continue;
            }
            
            ++child;
            dfs(i, n);
            low[n] = min(low[i], low[n]);

            if (low[i] >= dfsD[n]) flag = true;
        }

        // 如果 n 為根節點，則 child >= 2 就是割點
        // 否則只要 n 存在一個的 child，i 或 i 的 descendant 沒有 backedge ( 即 low[i] >= dfsD[n] ) 則 n 為割點
        if (flag && (child >= 2 || parent)) ++ret;
    };

    while (cin >> N && N)
    {
        cin.ignore();

        // init
        G.assign(N + 1, vector<int>());
        dfsD.assign(N + 1, 0);
        low.assign(N + 1, 0);
        time = 0;
        ret = 0;

        // 題目說最多 N 行，本來用 for 0 ~ N - 1 不知道為什麼會 WA，換成 0 ~ N 又會對，所以直接換成這樣
        while (getline(cin, str) && str != "0")
        {
            ss.clear();
            ss.str(str);

            int a, b;
            ss >> a;
            while (ss >> b)
            {   // 因為是無向圖，所以雙向都要建邊
                G[a].push_back(b);
                G[b].push_back(a);
            }
        }

        dfs(1, 0);
        
        cout << ret << '\n';
    }
}