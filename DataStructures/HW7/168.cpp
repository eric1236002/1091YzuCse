#include <iostream>
#include <functional>
#include <vector>
#include <string>

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
        vector<int> G[26];
        auto read = [&](int j) { return str[j] != ';' && str[j] != '.'; };
        for (int i = 0; i < SIZE(str);)
        {
            if (str[i] == ':')
            {
                int j = i + 1;
                while (read(j)) G[diff(str[i - 1])].push_back(diff(str[j++]));
                i = j + 1;
            }
            else ++i;
        }

        int steps = 0;
        int candle[26] = {};

        function<void(int, int)> dfs = [&](int M, int T)
        {
            // 放蠟燭
            if (steps && steps % k == 0) cout << char(T + 'A') << " ", candle[T] = 1;

            auto& v = G[M];
            for (int i = 0; i < SIZE(v); ++i)
            {
                // 如果 v[i] 沒有蠟燭且 t 不在 v[i] 那 M 就可以往 V[i] 走
                if (v[i] != T && !candle[v[i]])
                {
                    ++steps;
                    dfs(v[i], M);
                    return;
                }
            }

            // 如果 m 無路可走，代表會在 M 被抓到
            cout << '/' << char(M + 'A') << '\n';
        };

        dfs(m - 'A', t - 'A');
    }
}