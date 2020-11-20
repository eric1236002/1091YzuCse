#include <iostream>
#include <functional>
#include <vector>
#include <string>

#define LENGTH(str) int(str.length())
#define SIZE(c) int(c.size())
#define diff(ch) (ch - 'A')

using namespace std;

// reference: https://ppt.cc/fMYpGx

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int main()
{
    string str;
    
    while (cin >> str && str != "#")
    {
        int k;
        char m, t;
        cin >> m >> t >> k;

        // 讀取資料並建立圖
        vector<vector<char>> G(26);
        auto read = [&](int i, int j) { return str[j] != ';' && str[j] != '.'; };
        for (int i = 0; i < LENGTH(str);)
        {
            if (str[i] == ':')
            {
                int j = i + 1;
                while (read(i, j)) G[diff(str[i - 1])].push_back(str[j++]);
                i = j + 1;
            }
            else ++i;
        }

        int steps = 0;
        vector<int> candle(26);

        function<void(char, char)> dfs = [&](char M, char T)
        {
            // 放蠟燭
            if (steps && steps % k == 0) cout << T << " ", candle[diff(T)] = 1;

            auto& v = G[diff(M)];
            for (int i = 0; i < SIZE(v); ++i)
            {
                // 如果 v[i] 沒有蠟燭且 t 不在 v[i] 那 M 就可以往 V[i] 走
                if (v[i] != T && !candle[diff(v[i])])
                {
                    ++steps;
                    dfs(v[i], M);
                    return;
                }
            }

            // 如果 m 無路可走，代表會在 M 被抓到
            cout << '/' << M << '\n';
        };

        dfs(m, t);
    }
}