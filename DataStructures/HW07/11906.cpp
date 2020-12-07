#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

#define LOOP(n) for(int I = 0; I < n; ++I)

using namespace std;

// reference: https://ppt.cc/f7N4Ix

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int main()
{
    int T, Case = 0;
    cin >> T;

    LOOP(T)
    {
        int R, C, M, N, W;
        cin >> R >> C >> M >> N >> W;

        // 0 沒走過，>= 1 走過，-1 有水 ( 不能走 )
        vector<vector<int>> maps(R, vector<int>(C));

        LOOP(W)
        {
            int x, y;
            cin >> x >> y;
            maps[x][y] = -1;
        }

        function<void(int, int)> dfs = [&](int x, int y)
        {
            if (x < 0 || x >= R || y < 0 || y >= C || maps[x][y] == -1) return;

            // 如果當前的點已經有往下走過的話就只要增加可以走到當前的點的次數即可
            if (maps[x][y]++ != 0) return;

            int _x = M, _y = N;
            LOOP(2)
            {
                dfs(x + _x, y + _y);
                dfs(x - _x, y - _y);
                if (_x && _y)
                {
                    dfs(x + _x, y - _y);
                    dfs(x - _x, y + _y);
                }
                if (_x == _y) break;
                swap(_x, _y);
            }
        };

        dfs(0, 0);
        --maps[0][0];

        int odd = 0, even = 0;
        for (auto& v : maps) for (auto& i : v)
        {
            if (i <= 0) continue;
            i & 1 ? ++odd : ++even;
        }

        // 若 (0, 0) 只有在一開始的時候走到過，代表為 even
        if (!maps[0][0]) ++even;

        cout << "Case " << ++Case << ": " << even << ' ' << odd << '\n';
    }
}