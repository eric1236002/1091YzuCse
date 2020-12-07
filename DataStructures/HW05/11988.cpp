#include <iostream>
#include <list>
#include <string>

using namespace std;

static auto __ = []
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int main()
{
    string str;
    while (getline(cin, str) && !str.empty())
    {
        list<char> l;
        auto it = l.begin();
        for (auto& ch : str)
        {
            switch (ch)
            {
            case '[':
                it = l.begin();
                break;
            case ']':
                it = l.end();
                break;
            default:
                l.insert(it, ch);
                break;
            }
        }
        for (auto& ch : l) cout << ch;
        cout << '\n';
    }
}