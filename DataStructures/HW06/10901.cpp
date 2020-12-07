#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

// reference: https://ppt.cc/fNbc8x

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

    while (T--)
    {
        int n, t, m;
        cin >> n >> t >> m;

        queue<pair<int, int>> bank[2]; // 0 for left, 1 for right
        vector<int> arriveTime(m);

        auto [tmp, str] = make_pair(0, string());
        for (int i = 0; i < m; ++i)
        {
            cin >> tmp >> str;
            str == "left" ? bank[0].emplace(i, tmp) : bank[1].emplace(i, tmp);
        }

        auto [time, cur] = make_pair(0, 0);
        while (!bank[0].empty() || !bank[1].empty())
        {
            int closest = INT_MAX;
            if (!bank[0].empty()) closest = bank[0].front().second;
            if (!bank[1].empty()) closest = min(closest, bank[1].front().second);

            time = max(time, closest);

            int cnt = 0;
            while (!bank[cur].empty() && cnt < n && bank[cur].front().second <= time)
            {
                arriveTime[bank[cur].front().first] = time + t;
                bank[cur].pop();
                ++cnt;
            }

            cur ^= 1;
            time += t;
        }

        for (auto& i : arriveTime) cout << i << '\n';
        if (T) cout << '\n';
    }
}