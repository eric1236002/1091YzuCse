#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// fast IO
static auto __ = []()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

int main()
{
    int n;
    while (cin >> n && n)
    {
        unordered_map<string, int> m;

        while (n--)
        {
            string str;
            vector<string> v;
            for (int i = 0; i < 5; ++i) cin >> str, v.emplace_back(str);
            sort(begin(v), end(v));
            str.clear();
            for (auto& s : v) str += s;
            ++m[str];
        }

        pair<int, int> ret;
        for (auto& [k, v] : m)
        {
            if (v > ret.first) ret = { v, v };
            else if (v == ret.first) ret.second += v;
        }

        cout << ret.second << '\n';
    }
}