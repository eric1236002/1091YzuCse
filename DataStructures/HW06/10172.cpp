#include <iostream>
#include <stack>
#include <queue>

using namespace std;

// reference: https://ppt.cc/fIHBVx

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int main()
{
    int n, s, q;
    int T;
    cin >> T;
    while (T--)
    {
        stack<int> truck;
        queue<int> stationQueue[100];

        cin >> n >> s >> q;

        for (int i = 0; i < n; ++i)
        {
            int nc;
            cin >> nc;
            for (int j = 0; j < nc; ++j)
            {
                int target;
                cin >> target;
                stationQueue[i].push(target - 1);
            }
        }

        int cur = 0, time = 0;
        auto unload = [&]
        {
            return (!truck.empty() &&
                (truck.top() == cur || stationQueue[cur].size() < q));
        };

        while (true)
        {
            while (unload())
            {
                if (truck.top() != cur) stationQueue[cur].push(truck.top());
                truck.pop();
                ++time;
            }

            while (truck.size() < s && (!stationQueue[cur].empty()))
            {
                truck.push(stationQueue[cur].front());
                stationQueue[cur].pop();
                ++time;
            }

            bool clear = truck.empty();
            for (int i = 0; i < n && clear; ++i) clear &= stationQueue[i].empty();

            if (clear) break;

            cur = (cur + 1) % n;
            time += 2;
        }
        cout << time << '\n';
    }
}