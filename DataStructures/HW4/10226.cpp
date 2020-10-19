#include <iostream>
#include <string>
#include <map>
#include <iomanip>

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
    int c;
    string str;

    cin >> c;
    cin.ignore();
    // avoid space
    getline(cin, str);

    while (c--)
    {
        double cnt = 0;
        string str;
        map<string, double> m;

        while (getline(cin, str) && !str.empty()) ++m[str], ++cnt;
        
        for (auto& [tree, num] : m)
            cout << tree << " " << setprecision(4) << fixed << num * 100 / cnt << '\n';

        if(c) cout << '\n';
    }
}