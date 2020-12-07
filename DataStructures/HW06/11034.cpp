#include <iostream>
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
        int l, m;
        cin >> l >> m;

        // 0 for left, 1 for right
        queue<int> bank[2];

        auto [tmp, str] = make_pair(0, string());
        for (int i = 0; i < m; ++i)
        {
            cin >> tmp >> str;
            str == "left" ? bank[0].push(tmp) : bank[1].push(tmp);
        }

        int cnt = 0, cur = 0;
        while (!bank[0].empty() || !bank[1].empty())
        {
            int Cap = l * 100;
            while (!bank[cur].empty() && bank[cur].front() <= Cap)
                Cap -= bank[cur].front(), bank[cur].pop();
            cur ^= 1;
            ++cnt;
        }

        cout << cnt << '\n';
    }
}