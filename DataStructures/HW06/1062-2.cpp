#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int main()
{
    int cnt = 0;
    string in;
    while (cin >> in && in != "end")
    {
        int ret = 0, l = in.length();
        vector<int> dp(l, 1);
        for (int i = 0; i < l; ++i)
        {
            for (int j = i + 1; j < l; ++j)
                if (in[j] > in[i]) dp[j] = max(dp[j], dp[i] + 1);
            ret = max(ret, dp[i]);
        }
        cout << "Case " << ++cnt << ": " << ret << '\n';
    }
}