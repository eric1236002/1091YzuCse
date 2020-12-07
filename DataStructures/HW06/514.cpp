#include <iostream>
#include <queue>
#include <stack>

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
    int T, tmp;
    while (cin >> T && T)
    {
        while (cin >> tmp && tmp)
        {
            stack<int> s;
            queue<int> q;
            q.push(tmp);
            for (int i = 1; i < T; ++i) cin >> tmp, q.push(tmp);
            for (int i = 1; i <= T; ++i)
            {
                s.push(i);
                while (!s.empty() && s.top() == q.front()) s.pop(), q.pop();
            }
            cout << (s.empty() ? "Yes\n" : "No\n");
        }
        cout << '\n';
    }
}