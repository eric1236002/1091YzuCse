#include <iostream>
#include <string>
#include <stack>
#include <functional>

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
    string str, target;
    stack<char> s;

    function<void(int, int, string)> dfs = [&](int i1, int i2, string ret)
    {
        if (i2 == target.length()) { cout << ret << '\n'; return; }

        if (i1 < str.length())
        {
            s.push(str[i1]);
            dfs(i1 + 1, i2, ret + (ret.empty() ? "i" : " i"));
            s.pop();
        }

        if (!s.empty() && s.top() == target[i2])
        {
            auto tmp = s.top();
            s.pop();
            dfs(i1, i2 + 1, ret + (ret.empty() ? "o" : " o"));
            s.push(tmp);
        }
    };

    while (cin >> str >> target)
    {
        s = stack<char>();
        cout << "[\n";
        if (str.length() == target.length() && !str.empty()) dfs(0, 0, "");
        cout << "]\n";
    }
}