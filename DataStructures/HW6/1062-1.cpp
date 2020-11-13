#include <iostream>
#include <vector>
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
    int cnt = 0;
    string str;
    vector<stack<char>> v;

    auto AddToStack = [&](char& ch)
    {
        for (auto& s : v) if (ch <= s.top()) { s.push(ch); return; }
        v.push_back(stack<char>());
        v.back().push(ch);
    };

    while (cin >> str && str != "end")
    {
        v.clear();
        for (auto& ch : str) AddToStack(ch);
        cout << "Case " << ++cnt << ": " << v.size() << '\n';
    }
}