#include <iostream>
#include <set>

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
        long long ret = 0;
        multiset<int> s;
        for (int i = 0; i < n; ++i)
        {
            int num, tmp;
            cin >> num;
            for(int j = 0; j < num; ++j) cin >> tmp, s.insert(tmp);
            auto l = s.begin(), r = --s.end();
            ret += *r - *l;
            s.erase(l), s.erase(r);
        }
        cout << ret << '\n';
    }
}