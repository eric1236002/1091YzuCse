#include <iostream>
#include <unordered_map>
#include <list>

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
    char ch;
    int P, C, tmp, Case = 0;
    list<int> l;
    unordered_map<int, list<int>::iterator> m;
    while (cin >> P >> C && (P || C))
    {
        l.clear(), m.clear();
        cout << "Case " << ++Case << ":\n";
        for (int i = 1; i <= min(P, C); i++) m[i] = l.insert(l.end(), i);
        while (C--)
        {
            cin >> ch;
            if (ch == 'N')
            {
                cout << l.front() << '\n';
                m[l.front()] = l.insert(l.end(), l.front());
                l.pop_front();
            }
            else if (ch == 'E')
            {
                cin >> tmp;
                if (m.find(tmp) != m.end()) l.erase(m[tmp]);
                m[tmp] = l.insert(l.begin(), tmp);
            }
        }
    }
}