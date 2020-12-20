#include <iostream>
#include <string>
#include <stack>

using namespace std;

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

bool solve(string& str)
{
    stack<char> s;
    for (auto& ch : str)
    {
        switch (ch)
        {
        case ')':
            if (s.empty() || s.top() != '(') return false;
            s.pop();
            break;
        case ']':
            if (s.empty() || s.top() != '[') return false;
            s.pop();
            break;
        default:
            s.push(ch);
            break;
        }
    }
    return s.empty();
}

int main()
{
    int T;
    string str;
    cin >> T;
    cin.ignore();
    while (T--)
    {
        getline(cin, str);
        if (solve(str)) cout << "Yes\n";
        else cout << "No\n";
    }
}