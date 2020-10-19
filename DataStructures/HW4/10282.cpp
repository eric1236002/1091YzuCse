#include <iostream>
#include <string>
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
    string key, val;
    unordered_map<string, string> m;
    
    while (getline(cin, val))
    {
        if (val.empty()) break;
        int idx = val.find(' ');
        key = val.substr(idx + 1, val.length() - idx);
        val.erase(idx);
        m[key] = val;
    }
    while (getline(cin, key))
    {
        if (key.empty()) break;
        m.count(key) ? cout << m[key] << '\n' : cout << "eh\n";
    }
}